#include <stdio.h>
#include "../components/led_strip/src/led_strip_rmt_ws2812.c"
#include "../components/blocking_delay/blocking_delay.c"
#include "../components/led_control/include/led_control.c"
#include "driver/touch_pad.h"

led_strip_t *strip;

int intensidad = 0;

void handle_touch_up() {
    if (intensidad < 100) {
        intensidad += 10 ;
    }
    printf("intensidad: %d\n", intensidad);
    encender_led_custom(strip, 0, 2.55 * intensidad, 0, 0);

}

void handle_touch_down() {
    if (intensidad >= 10) {
        intensidad -= 10;
    }
    printf("intensidad: %d\n", intensidad);
    encender_led_custom(strip, 0, 2.55 * intensidad, 0, 0);

}

int app_main(void)
{
    // Inicializar el LED
      if (led_rgb_init(&strip) != ESP_OK) {
          printf("Error al inicializar la tira de LED\n"); // Si hay error se imprime por pantalla
          return -1;
      }

    // Inicializar el touch pad
    touch_pad_init();
    // Configurar los botones a utilizar
    touch_pad_config(TOUCH_PAD_NUM1);
    touch_pad_config(TOUCH_PAD_NUM3);
    // Setear modo de funcionamiento
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_fsm_start();

    uint32_t up_value;
    uint32_t down_value;

    delay_ms(100);

    // Leer el valor del touch pad cada x milisegundos
    while (1) {
        touch_pad_read_raw_data(TOUCH_PAD_NUM1, &up_value);
        // printf("Up: [%lu] \n",  up_value);
        touch_pad_read_raw_data(TOUCH_PAD_NUM3, &down_value);
        // printf("Down: [%lu] \n",  down_value);

        if (up_value > 52000) {
            handle_touch_up();
        }
        if (down_value > 52000) {
            handle_touch_down();
        }

        delay_ms(200);
    }

    // Limpiar antes de salir
    strip->clear(strip, 100);
    strip->del(strip);
    return 0;
}
