#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_system.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "uart_esp.h"

#define BUTTON_ENTER '\r'

void app_main(void)
{  
    /* Configura a uart */
    config_uart(UART_NUM_0);
    /* Configura um caracter para gerar um evento - neste caso é o '\r' */
    config_uart_pattern(UART_NUM_0, BUTTON_ENTER);
    /* Inicializa a uart0 para receber dados na serial */
    init_serial();
   
    /* Deleta a task app_main */
    vTaskDelete(NULL);
}