#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/touch_pad.h"
#include "esp_log.h"


void app_main(void)
{
    /* Initialize touch pad peripheral. */
    touch_pad_init();
    touch_pad_config(TOUCH_PAD_NUM6);
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_fsm_start();

 uint32_t touch_value;

    /* Wait touch sensor init done */
    vTaskDelay(100 / portTICK_PERIOD_MS);
    printf("Touch Sensor read, the output format is: \nTouchpad num:[raw data]\n\n");

    while (1) {
        touch_pad_read_raw_data(TOUCH_PAD_NUM6, &touch_value);    // read raw data.
        printf("T%d: [%4lu] ", TOUCH_PAD_NUM6, touch_value);
        
        printf("\n");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}
