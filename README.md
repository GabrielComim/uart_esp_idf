# Projeto: Comunicação UART no ESP32 usando ESP-IDF

Autor: Gabriel Comim

---

## Descrição

Este projeto demonstra como implementar comunicação serial **UART (Universal Asynchronous Receiver/Transmitter)** utilizando o framework **ESP-IDF** da Espressif no microcontrolador **ESP32**.

A aplicação é focada na leitura de dados recebidos pela **UART0**, usando uma task dedicada para tratamento dos eventos da UART.

---

## Objetivo

Realizar a captura de dados recebidos via UART e processá-los ao detectar um caractere específico. Neste exemplo, o caractere delimitador utilizado é o **'\r' (ENTER)**.

Sempre que o **ENTER** é recebido na UART, o programa realiza a leitura de todos os dados acumulados no buffer e processa a informação.

---

## Tecnologias utilizadas

- **Placa de desenvolvimento: ESP32**
- **Framework: ESP-IDF**
  
---

## Funcionamento

- A aplicação cria uma **task dedicada** para monitorar eventos da UART.
- O driver da UART é configurado para gerar eventos a cada novo caractere recebido.
- Quando o caractere **'\r' (ENTER)** é detectado, a task lê o buffer da UART e processa os dados recebidos.

---

## Palavras-chave
ESP32, UART, ESP-IDF, Comunicação Serial, UART0, Eventos UART, FreeRTOS, Gabriel Comim






