#pragma once

#include "drivers/clock.h"
#include "drivers/gpio.h"
#include "drivers/keypad.h"

#define BTN_LEFT    0
#define BTN_RIGHT   1
#define BTN_UP      2
#define BTN_DOWN    3
#define BTN_ACTION  4
#define LONG_PRESS_PERIOD   3000

struct ButtonState {
    uint8_t pin = 0;
    uint8_t (*get_state)() = NULL;
    uint8_t state = 1;
    uint32_t ts = 0;
};

ButtonState buttons[] = {
    {
        .get_state = JOY_left_pressed,
    },
    {
        .get_state = JOY_right_pressed,
    },
    {
        .get_state = JOY_up_pressed,
    },
    {
        .get_state = JOY_down_pressed,
    },
    {
        .get_state = JOY_act_pressed,
    },
};

#define BUTTON_NO_ACTION    0
#define BUTTON_CLICK        1
#define BUTTON_LONG_CLICK   2

void button_setup() {
    for (uint8_t i = 0; i < sizeof(buttons) / sizeof(ButtonState); ++i) {
        if (buttons[i].pin != 0) {
            PIN_input_PU(buttons[BTN_LEFT].pin);
        }
    }
    JOY_init();
}

int check_button(int index) {
    ADC_input(PIN_PAD);
    int old_state = buttons[index].state;
    int new_state = old_state;
    if (buttons[index].pin != 0) {
        new_state = PIN_read(buttons[index].pin);
    } else if (buttons[index].get_state != NULL) {
        new_state = buttons[index].get_state() ? 0 : 1;
    }
    int action = BUTTON_NO_ACTION;
    if (new_state != old_state) {
        if (new_state == 1) {
            if (millis() - buttons[index].ts > LONG_PRESS_PERIOD) {
                action = BUTTON_LONG_CLICK;
            } else {
                action = BUTTON_CLICK;
            }
        }
        buttons[index].state = new_state;
        buttons[index].ts = millis();
    }

    return action;
}
