#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x.h>
#include "gpio.h"
#include "oled_min.h"
#include <math.h>

#define PIN_LED_PWM     PA1
#define PIN_LED_PWR_EN  PC6
#define PIN_FAN_PWR_EN  PC7
#define PIN_NTC_ADC     PD2
#define PIN_BAT_ADC     PD3

void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp);

static inline void dev_control_init() {
    PIN_output_PP(PIN_FAN_PWR_EN);
    PIN_high(PIN_FAN_PWR_EN);

    PIN_output_PP(PIN_LED_PWR_EN);
    PIN_high(PIN_LED_PWR_EN);

    PIN_input_AN(PIN_NTC_ADC);
    PIN_input_AN(PIN_BAT_ADC);

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    PIN_low(PIN_LED_PWR_EN);
    PIN_output_PP(PIN_LED_PWM);
    PIN_high(PIN_LED_PWM);
    delay(1);
    PIN_low(PIN_LED_PWM);
    PIN_high(PIN_LED_PWR_EN);

    TIM1_PWMOut_Init( 100, 24-1, 0 );
}

static inline void dev_led_enable(bool enable) {
    PIN_write(PIN_LED_PWR_EN, enable ? 0 : 1);
}

static inline void dev_fan_enable(bool enable) {
    PIN_write(PIN_FAN_PWR_EN, enable ? 0 : 1);
}

static inline uint16_t dev_adc_read(int pin) {
    ADC_fast();
    ADC_input_VREF();
    ADC_read();
    int32_t vref = ADC_read();

    ADC_fast();
    ADC_input(pin);
    ADC_read();
    uint32_t val_sum = 0;
    for (int i = 0; i < 4; ++i) {
        val_sum += ADC_read();
    }
    uint32_t val = val_sum >> 2;
    val = 1200 * val / vref;
    return val;
}

#define R_FIXED 10000

const int32_t r_ntc_table[] = {
    345275, 322791, 301925, 282549, 264549, 247816, 232254, 217774, 204292, 191735, 180032, 169120, 158941, 149441, 140571, 132284, 124522, 117266, 110480, 104130, 98185, 92618, 87402, 82513, 77927, 73626, 69588, 65797, 62237, 58890, 55744, 52786, 50002, 47382, 44916, 42592, 40400, 38333, 36385, 34548, 32814, 31179, 29636, 28178, 26800, 25497, 24263, 23096, 21992, 20947, 19958, 19022, 18135, 17294, 16498, 15742, 15025, 14345, 13699, 13086, 12504, 11951, 11426, 10926, 10452, 10000, 9570, 9162, 8773, 8402, 8049, 7713, 7393, 7088, 6797, 6520, 6255, 6003, 5762, 5532, 5313, 5103, 4903, 4711, 4529, 4354, 4187, 4027, 3874, 3728, 3588, 3454, 3326, 3203, 3086, 2973, 2865, 2761, 2662, 2567, 2476, 2388, 2304, 2224, 2146, 2072, 2001, 1932, 1866, 1803, 1742, 1684, 1628, 1574, 1522, 1472, 1424, 1378, 1333, 1290, 1249, 1209, 1171, 1134, 1099, 1065, 1032, 1000, 969, 940, 911, 884, 857, 831, 807, 783, 760, 738, 716, 695, 675, 656, 637, 619, 602, 585, 569, 553, 538, 523, 508, 495, 481, 468, 456, 443, 432, 420, 409, 399, 388, 378, 368, 359, 350, 341
};
#define R_NTC_TABLE_LEN     (sizeof(r_ntc_table)/sizeof(int32_t))
#define R_NTC_TEMP_START    -40

static inline uint16_t dev_ntc_read() {
    int32_t v_out_mv = dev_adc_read(PIN_NTC_ADC);

    ADC_fast();
    ADC_input_VREF();
    ADC_read();
    int32_t vref = ADC_read();
    int32_t vpwr = 1200 * 1024 / vref;

    // 计算热敏ek电阻的阻值
    int32_t r_ntc = R_FIXED * v_out_mv * 2 / vpwr;

    int16_t t_celsius = R_NTC_TEMP_START;
    for (uint8_t i = 0; i < R_NTC_TABLE_LEN; ++i) {
        if (r_ntc > r_ntc_table[i]) {
            break;
        }
        t_celsius++;
    }

    return t_celsius;
}

static inline uint16_t dev_bat_read() {
    int32_t val = dev_adc_read(PIN_BAT_ADC);
    int32_t volt = val * 2;
    volt /= 100;
    return volt;
}


/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2   1

/* PWM Output Mode Selection */
#define PWM_MODE PWM_MODE1
// #define PWM_MODE PWM_MODE2
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

#if (PWM_MODE == PWM_MODE1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

#elif (PWM_MODE == PWM_MODE2)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

#endif

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init( TIM1, &TIM_OCInitStructure );

    TIM_CtrlPWMOutputs(TIM1, ENABLE );
    TIM_OC2PreloadConfig( TIM1, TIM_OCPreload_Disable );
    TIM_ARRPreloadConfig( TIM1, ENABLE );
    TIM_Cmd( TIM1, ENABLE );
}



#ifdef __cplusplus
};
#endif