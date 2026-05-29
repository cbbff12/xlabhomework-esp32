extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"    
#include <string.h>                  
}
#include "init.h"
typedef struct {
    gpio_num_t gpio_num;
    int time; 
    int delay;
} led_config;
#define LED_GPIO GPIO_NUM_2
void led_init(gpio_num_t num)
{
    // 配置GPIO为输出模式
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << num),  // 选择要配置的GPIO引脚
        .mode = GPIO_MODE_OUTPUT,            // 设置为输出模式
        .pull_up_en = GPIO_PULLUP_DISABLE,   // 禁用上拉电阻
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // 禁用下拉电阻
        .intr_type = GPIO_INTR_DISABLE       // 禁用中断
    };
    
    // 应用GPIO配置
    gpio_config(&io_conf);
    
    // 初始状态设置为低电平（LED关闭）
    gpio_set_level(LED_GPIO, 0);
}
void led_task(void *pvParameters)
{
    led_config *led1_config = (led_config *)pvParameters;
    int time = led1_config->time;
    gpio_num_t gpio_num = led1_config->gpio_num;
    int delay = led1_config->delay;
    vTaskDelay(pdMS_TO_TICKS(delay));  
    
    while (1) {
        // 翻转LED1状态
        gpio_set_level(gpio_num, 1);
        vTaskDelay(pdMS_TO_TICKS(time)); 
        gpio_set_level(gpio_num, 0);
        vTaskDelay(pdMS_TO_TICKS(time));  
    }
}
void led_control(void *pvParameters)
{
    gpio_set_level(GPIO_NUM_13, 0);
    gpio_set_level(GPIO_NUM_25, 0);
    char* led_status = (char *)malloc(128);
    while (1) {
        if (scanf("%127s", led_status) == 1) {
            printf("%s", led_status);
            if(led_status[0] == '1'){
                gpio_set_level(GPIO_NUM_13, 1);
                gpio_set_level(GPIO_NUM_25, 0);
            }
            else if(led_status[0] == '0'){
                gpio_set_level(GPIO_NUM_13, 0);
                gpio_set_level(GPIO_NUM_25, 1);
            }
            vTaskDelay(pdMS_TO_TICKS(100));  
        }
    }
}