#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"    
#include <stdlib.h>
#include "init.h"

#define UART_NUM            UART_NUM_0          // 使用UART0（默认连接电脑串口）
#define BUF_SIZE            (1024)              // 缓冲区大小
#define TXD_PIN             UART_PIN_NO_CHANGE  // 使用默认TX引脚
#define RXD_PIN             UART_PIN_NO_CHANGE  // 使用默认RX引脚


void uart_echo_task(void *pvParameters)
{
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);
    if (data == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory");
        vTaskDelete(NULL);
        return;
    }

    while (1) {
        // 读取从电脑串口发送过来的数据
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE - 1, pdMS_TO_TICKS(100));
        
        if (len > 0) {
            data[len] = '\0';  // 添加字符串结束符，便于打印
            ESP_LOGI(TAG, "Received: %s (length: %d)", (char *)data, len);
            
            
            //uart_write_bytes(UART_NUM, (const char *)data, len);// 将收到的数据原样发送回电脑串口
            if(data[0] == '1'){
                gpio_set_level(GPIO_NUM_13, 1);
                gpio_set_level(GPIO_NUM_25, 0);
            }
            else if(data[0] == '2'){
                gpio_set_level(GPIO_NUM_13, 0);
                gpio_set_level(GPIO_NUM_25, 1);
            }
        }
        
        // 短暂延时让出CPU
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
    free(data);
    vTaskDelete(NULL);
}