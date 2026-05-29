#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"  // 用于微秒级延时
#include "init.h"
#include "led.h"
#include "esp_task_wdt.h"

#define IN1_PIN GPIO_NUM_21
#define IN2_PIN GPIO_NUM_19
#define IN3_PIN GPIO_NUM_18
#define IN4_PIN GPIO_NUM_5
#define STEP_DELAY_US 2000
void stepper_init(void){
    led_init(GPIO_NUM_5);
    led_init(GPIO_NUM_18);
    led_init(GPIO_NUM_19);
    led_init(GPIO_NUM_21);
}
void step_forward(void *pvParameters) {
    led_config *led1_config = (led_config *)pvParameters;
    int time = led1_config->time;
    gpio_num_t gpio_num = led1_config->gpio_num;
    int delay = led1_config->delay;
    printf("step_forward\n");
    for(int i = 0; i < delay; i++){

    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);

    taskYIELD();
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    printf("step_forward\n");
    vTaskDelete(NULL);

}
void step_backward(void *pvParameters) {
    led_config *led1_config = (led_config *)pvParameters;
    int time = led1_config->time;
    gpio_num_t gpio_num = led1_config->gpio_num;
    int delay = led1_config->delay;
    int i = 0;
    printf("step_backward\n");
    for(i = 0; i < delay; i++){
        
    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 1);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 1); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 0); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 1);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);
    

    gpio_set_level(IN1_PIN, 1); gpio_set_level(IN2_PIN, 0);
    gpio_set_level(IN3_PIN, 0); gpio_set_level(IN4_PIN, 0);
    esp_rom_delay_us(STEP_DELAY_US);

    taskYIELD();
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    
    printf("step_backward\n");
    vTaskDelete(NULL);
}