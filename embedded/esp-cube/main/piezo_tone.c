#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#define LEDC_GPIO_PIN           0
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 4 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096

//some useful Major notes Frequenties in same octave
typedef enum
{
    A   = 440,
    Bb  = 466, // B flat
    B   = 494,
    C   = 523,
    Csh = 554, // C sharp
    D   = 587,
    Dsh = 622,
    E   = 659,
    F   = 698,
    Fsh = 740,
    G   = 740,
    Ab  = 831,
    Aa   = 880 // Next octave

}notesHz;

notesHz note = E;



void init_piezo_tone(){
        // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = note, 
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_GPIO_PIN,
        .duty           = LEDC_DUTY,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    ledc_timer_pause(LEDC_MODE,LEDC_TIMER);
}

void piezo_countdown(){
    ledc_set_freq(LEDC_MODE,LEDC_TIMER, note);
    for (size_t i = 0; i < 5; i++)
    {
        ledc_timer_resume(LEDC_MODE,LEDC_TIMER);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        ledc_timer_pause(LEDC_MODE,LEDC_TIMER);
        vTaskDelay(500 / portTICK_PERIOD_MS); 
    }
    note = C;
    ledc_set_freq(LEDC_MODE,LEDC_TIMER, note);
    ledc_timer_resume(LEDC_MODE,LEDC_TIMER);
    vTaskDelay(1400 / portTICK_PERIOD_MS); 
    ledc_timer_pause(LEDC_MODE,LEDC_TIMER);
}



void app_main() {
    init_piezo_tone();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    piezo_countdown();
    
}
