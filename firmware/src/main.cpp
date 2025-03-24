#include <ch32v00x.h>
#include <debug.h>

#include "display.hpp"
#include "button.hpp"
#include "drivers/keypad.h"
#include "drivers/dev_control.h"
#include "myformat.h"

extern "C" void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
extern "C" void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

#define LED_MAX_ON_TIME 300
#define LED_TIMER_MAX   120
#define LED_TIMER_STEP  10
#define LED_POWER_MAX   100
#define LED_POWER_MIN   10
#define LED_POWER_STEP  10
bool fan_enabled = false;
bool led_enabled = false;
int led_timer = 0;
int32_t led_start_time = 0;
int led_power = 100;

void show_current_state() {
    char buf[17];
    display_clear();

    int bat = dev_bat_read();
    my_printf3(buf, 17, (const char *)"Temp %d Bat %d.%d", dev_ntc_read(), bat / 10, bat % 10);
    display_write_line(0, buf);

    strcpy(buf, "Fan OFF LED OFF");
    if (fan_enabled) {
        memcpy(buf + 4, "ON ", 3);
    }
    if (led_enabled) {
        memcpy(buf + 12, "ON ", 3);
    }
    display_write_line(1, buf);

    if (led_timer == 0) {
        my_printf1(buf, 17, "Time INF Pwr %d", led_power);
    } else {
        my_printf2(buf, 17, "Time %d Pwr %d", led_timer, led_power);
    }
    display_write_line(2, buf);

    if (led_enabled) {
        int time_passed = millis() - led_start_time;
        int show_time = time_passed / 1000;
        if (led_timer != 0) {
            // time left
            show_time = led_timer - (time_passed / 1000);
        }
        my_printf1(buf, 17, "Running %ds      ", show_time);
        int progress = (time_passed / 200) % 5;
        for (int i = 0; i < progress; ++i) {
            buf[12 + i] = '>';
        }
        buf[16] = 0;
    } else {
        strcpy(buf, "PRESS TO START");
    }
    display_write_line(3, buf);

    display_flush();
}

int main(void)
{
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    systick_init();
    USART_Printf_Init(115200);

    // Delay_Ms(1000); // give serial monitor time to open
    // printf("SystemClk: %u\r\n", (unsigned)SystemCoreClock);
    // printf("DeviceID: %08x\r\n", (unsigned)DBGMCU_GetDEVID());

    display_init();
    display_clear();
    display_flush();

    button_setup();
    dev_control_init();

    while (1) {
        if (!led_enabled) {
            if (check_button(BTN_LEFT) == BUTTON_CLICK) {
                led_timer = led_timer == 0 ? LED_TIMER_MAX : led_timer - LED_TIMER_STEP;
            }

            if (check_button(BTN_RIGHT) == BUTTON_CLICK) {
                led_timer = led_timer == LED_TIMER_MAX ? 0 : led_timer + LED_TIMER_STEP;
            }
        }

        if (check_button(BTN_DOWN) == BUTTON_CLICK) {
            led_power = led_power == LED_POWER_MIN ? LED_POWER_MAX : led_power - LED_POWER_STEP;
        }

        if (check_button(BTN_UP) == BUTTON_CLICK) {
            led_power = led_power == LED_POWER_MAX ? LED_POWER_MIN : led_power + LED_POWER_STEP;
        }

        if (check_button(BTN_ACTION) == BUTTON_CLICK) {
            led_enabled = !led_enabled;
            dev_led_enable(led_enabled);

            fan_enabled = !fan_enabled;
            dev_fan_enable(fan_enabled);

            if (led_enabled) {
                led_start_time = millis();
            }
        }

        bool should_stop = false;
        int32_t time_passed = millis() - led_start_time;
        if (led_timer > 0 && led_enabled) {
            if (time_passed > led_timer * 1000) {
                should_stop = true;
            }
        }
        if (led_timer == 0 && time_passed >= LED_MAX_ON_TIME * 1000) {
            should_stop = true;
        }
        if (should_stop) {
            led_enabled = false;
            dev_led_enable(led_enabled);
            fan_enabled = false;
            dev_fan_enable(fan_enabled);
        }

        if (led_enabled) {
            TIM1->CH2CVR = led_power;
        } else {
            TIM1->CH2CVR = 0;
        }

        show_current_state();
    }
}

void NMI_Handler(void) {}
void HardFault_Handler(void)
{
    while (1)
    {
    }
}
