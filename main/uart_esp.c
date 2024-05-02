/**
 * @file uart_esp.c
 * @author Gabriel Comim
 * @brief Configura a uart via esp idf. 
 *        Possui implementação de task para leitura dos eventos da UART.
 *        Neste exemplo, recebe dados via UART0.
 * 
 * @version 1.1
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "uart_esp.h"

QueueHandle_t uart_queue;

/* Variável para leitura dos dados recebidos pela uart */
char buff_read_uart[BUFFER_READ_UART_SIZE];

void config_uart(uart_port_t uart_number)
{
    uart_config_t uart_cfg = 
    {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
    };
    
    ESP_ERROR_CHECK(uart_driver_install(uart_number, BUFFER_UART_SIZE, BUFFER_UART_SIZE, QUEUE_UART_SIZE, &uart_queue, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_number, &uart_cfg));
    ESP_ERROR_CHECK(uart_set_pin(uart_number, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    
    ESP_LOGI("UART", "UART INICIALIZADO COM SUCESSO");
}

int uart_sendString(uart_port_t uart_number, char *str)
{
    return uart_write_bytes(uart_number, (const char*)str, strlen(str));
}

void config_uart_pattern(uart_port_t uart_number, char pattern)
{
    ESP_ERROR_CHECK(uart_enable_pattern_det_baud_intr(uart_number, pattern, PATTERN_CHR_NUM, 1, 0, 0));
    uart_pattern_queue_reset(uart_number, QUEUE_UART_SIZE);
}

void event_uart(uart_port_t uart_number, uart_event_t uart_event, char *read_uart, QueueHandle_t *uart_queue)
{
    switch(uart_event.type)
    {
        case UART_DATA:
            // ESP_LOGI("TASK", "UART DATA");
            break;
          
        case UART_PATTERN_DET:            
            int header_pos = uart_pattern_pop_pos(uart_number);
            int bytes_read = 0;

            bytes_read = uart_read_bytes(uart_number, read_uart, header_pos, pdMS_TO_TICKS(100));
              
            // se não leu nenhum byte ou a função retornou um erro, retorna false
            if(bytes_read == 0 || bytes_read == -1)
            {
                ESP_LOGI("TASK", "UART NO DATA RECEIVE");
            }
            else 
            {
                ESP_LOGI("UART", " %s", read_uart);
            }
            /* Descarta todo dado que esteja no buffer de RX */
            uart_flush(uart_number);
            /* Zera o buffer de leitura da uart */
            bzero(read_uart, BUFFER_READ_UART_SIZE);      
            
            break;
          
        case UART_BUFFER_FULL:
            ESP_LOGI("TASK", "RING BUFFER FULL");
            
            uart_flush_input(uart_number);
            xQueueReset(uart_queue);
            
            break;
              
        default:
            ESP_LOGI("TASK", "UART EVENT TYPE: %d", uart_event.type);
              
            break;
    }
}

static void uart_task(void *arg)
{
    // QueueHandle_t *uart_task_queue = (QueueHandle_t*)arg;
    /* Inicializa eventos da uart */
    uart_event_t uart_event;
    
    /* Zera o buffer */
    bzero(buff_read_uart, BUFFER_READ_UART_SIZE);      
        
      //Waiting for UART event.
      while(true)
      {
        // espera até que uma mensagem seja recebida na fila
        xQueueReceive(uart_queue, (void *)&uart_event, portMAX_DELAY);

        /* Verifica o evento da uart */  
        event_uart(UART_NUM_0, uart_event, &buff_read_uart, &uart_queue);

        vTaskDelay(pdMS_TO_TICKS(50));
      }
}

void init_serial()
{
    /* Cria a task para a UART */
    xTaskCreatePinnedToCore(uart_task, "uart_task", 4096, NULL, 5, NULL, 1);
    ESP_LOGI("UART", "AGUARDA ENTRADA UART:");
}
