#ifndef UART_ESP_H
#define UART_ESP_H

#include "stdio.h"
#include "stdlib.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define QUEUE_UART_SIZE 10
#define BUFFER_UART_SIZE 2048
#define BUFFER_READ_UART_SIZE 100
#define PATTERN_CHR_NUM 1

/**
 * @brief Configuração da UART.
 * 
 * @param uart_number Define a porta da UART. 
 */
void config_uart(uart_port_t uart_number);

/**
 * @brief Inicializa o evento por padrão, isto é, aguarda um caracter específico para gerar uma interrupção em event uart.
 * 
 * @param uart_number   Define a porta da UART. 
 * @param pattern       Qual padrão finaliza a leitura da uart
 */
void config_uart_pattern(uart_port_t uart_number, char pattern);

/**
 * @brief 
 * 
 * @param uart_number   Define a porta da UART. 
 * @param uart_event    struct com os tipos da uart
 * @param read_uart     Armazena o valor lido na uart
 * @param uart_queue    Informa a fila da uart
 */
void event_uart(uart_port_t uart_number, uart_event_t uart_event, char *read_uart, QueueHandle_t *uart_queue);

/**
 * @brief Inicializa a task da uart
 * 
 */
void init_serial();

#endif      // UART_H