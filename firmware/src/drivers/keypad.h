#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <ch32v00x.h>
#include "gpio.h"
#include "oled_min.h"

// Pin assignments
#define PIN_ACT     PA2   // pin connected to fire button
#define PIN_PAD     PC4   // pin conected to direction buttons

// Joypad calibration values
#define JOY_N       197   // joypad UP
#define JOY_NE      259   // joypad UP + RIGHT
#define JOY_E       90    // joypad RIGHT
#define JOY_SE      388   // joypad DOWN + RIGHT
#define JOY_S       346   // joypad DOWN
#define JOY_SW      616   // joypad DOWN + LEFT
#define JOY_W       511   // joypad LEFT
#define JOY_NW      567   // JOYPAD UP + LEFT
#define JOY_DEV     20    // deviation

// Sound enable
#define JOY_SOUND   1     // 0: no sound, 1: with sound

// Game slow-down delay
#define JOY_SLOWDOWN()    DLY_us(600)

// Init driver
static inline void JOY_init(void) {
  PIN_input_AN(PIN_PAD);
  PIN_input_PU(PIN_ACT);
//   PIN_output(PIN_BEEP);
//   PIN_high(PIN_BEEP);
//   OLED_init();
  ADC_init();
  ADC_input(PIN_PAD);
}

// Buttons
// #define JOY_act_pressed()         (PIN_read(PIN_ACT) ? 1 : 0)
// #define JOY_act_released()        (PIN_read(PIN_ACT) ? 1 : 0)
#define JOY_pad_pressed()         (ADC_read() > 10)
#define JOY_pad_released()        (ADC_read() <= 10)
// #define JOY_all_released()        (JOY_act_released() && JOY_pad_released())

static inline uint8_t JOY_act_pressed(void) {
    return PIN_read(PIN_ACT);
}

static inline uint8_t JOY_up_pressed(void) {
 uint16_t val = ADC_read();
 return(   ((val > JOY_N  - JOY_DEV) && (val < JOY_N  + JOY_DEV))
         | ((val > JOY_NE - JOY_DEV) && (val < JOY_NE + JOY_DEV))
         | ((val > JOY_NW - JOY_DEV) && (val < JOY_NW + JOY_DEV)) );
}

static inline uint8_t JOY_down_pressed(void) {
 uint16_t val = ADC_read();
 return(   ((val > JOY_S  - JOY_DEV) && (val < JOY_S  + JOY_DEV))
         | ((val > JOY_SE - JOY_DEV) && (val < JOY_SE + JOY_DEV))
         | ((val > JOY_SW - JOY_DEV) && (val < JOY_SW + JOY_DEV)) );
}

static inline uint8_t JOY_left_pressed(void) {
 uint16_t val = ADC_read();
 return(   ((val > JOY_W  - JOY_DEV) && (val < JOY_W  + JOY_DEV))
         | ((val > JOY_NW - JOY_DEV) && (val < JOY_NW + JOY_DEV))
         | ((val > JOY_SW - JOY_DEV) && (val < JOY_SW + JOY_DEV)) );
}

static inline uint8_t JOY_right_pressed(void) {
 uint16_t val = ADC_read();
 return(   ((val > JOY_E  - JOY_DEV) && (val < JOY_E  + JOY_DEV))
         | ((val > JOY_NE - JOY_DEV) && (val < JOY_NE + JOY_DEV))
         | ((val > JOY_SE - JOY_DEV) && (val < JOY_SE + JOY_DEV)) );
}


#ifdef __cplusplus
};
#endif