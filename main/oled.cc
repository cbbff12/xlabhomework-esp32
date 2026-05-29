#include "oled.h"
void i2c_master_init(void);
void oled_write_cmd(uint8_t cmd);
void oled_write_data(uint8_t* data, size_t len);
void oled_init(void);
void oled_display_frame(const unsigned char* frame_data);
void video_player_task(void *pvParameters);
void oled_test_pattern(void *pvParameters);
