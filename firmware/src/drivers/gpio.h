// ===================================================================================
// Basic GPIO Functions for CH32V003                                          * v1.5 *
// ===================================================================================
//
// Pins must be defined as PA0, PA1, .., PC0, PC1, etc. - e.g.:
// #define PIN_LED PC0      // LED on pin PC0
//
// PIN functions available:
// ------------------------
// PIN_input(PIN)           Set PIN as INPUT (floating, no pullup/pulldown)
// PIN_input_PU(PIN)        Set PIN as INPUT with internal PULLUP resistor
// PIN_input_PD(PIN)        Set PIN as INPUT with internal PULLDOWN resistor
// PIN_input_AN(PIN)        Set PIN as INPUT for analog peripherals (e.g. ADC) (*)
// PIN_output(PIN)          Set PIN as OUTPUT (push-pull)
// PIN_output_OD(PIN)       Set PIN as OUTPUT (open-drain)
// PIN_alternate(PIN)       Set PIN as alternate output (push-pull)
// PIN_alternate_OD(PIN)    Set PIN as alternate output (open-drain)
//
// PIN_low(PIN)             Set PIN output value to LOW (*)
// PIN_high(PIN)            Set PIN output value to HIGH
// PIN_toggle(PIN)          TOGGLE PIN output value
// PIN_read(PIN)            Read PIN input value
// PIN_write(PIN, val)      Write PIN output value (0 = LOW / 1 = HIGH)
//
// PORT functions available:
// -------------------------
// PORT_enable(PIN)         Enable GPIO PORT of PIN
// PORTA_enable()           Enable GPIO PORT A
// PORTC_enable()           Enable GPIO PORT C
// PORTD_enable()           Enable GPIO PORT D
// PORTS_enable()           Enable all GPIO PORTS
//
// PORT_disable(PIN)        Disable GPIO PORT of PIN
// PORTA_disable()          Disable GPIO PORT A
// PORTC_disable()          Disable GPIO PORT C
// PORTD_disable()          Disable GPIO PORT D
// PORTS_disable()          Disable all GPIO PORTS
//
// Analog-to-Digital Converter (ADC) functions available:
// ------------------------------------------------------
// ADC_init()               Init, enable and calibrate ADC (must be called first)
// ADC_enable()             Enable ADC (power-up)
// ADC_disable()            Disable ADC (power-down)
// ADC_calibrate()          Calibrate ADC
//
// ADC_fast()               Set fast mode   ( 28 clock cycles, least accurate) (*)
// ADC_medium()             Set medium mode (168 clock cycles, medium accurate)
// ADC_slow()               Set slow mode   (504 clock cycles, most accurate)
//
// ADC_input(PIN)           Set PIN as ADC input
// ADC_input_VREF()         Set internal voltage referece (Vref) as ADC input
// ADC_input_VCAL()         Set calibration voltage (Vcal) as ADC input
//
// ADC_read()               Sample and read ADC value (0..1023)
// ADC_read_VDD()           Sample and read supply voltage (VDD) in millivolts (mV)
//
// Op-Amp Comparator (OPA) functions available:
// --------------------------------------------
// OPA_enable()             Enable OPA comparator
// OPA_disable()            Disable OPA comparator
// OPA_negative(PIN)        Set OPA inverting input PIN (PA1, PD0 only)
// OPA_positive(PIN)        Set OPA non-inverting input PIN (PA2, PD7 only)
// OPA_output()             Enable OPA output (push-pull) on pin PD4
// OPA_output_OD()          Enable OPA output (open-drain) on pin PD4
// OPA_read()               Read OPA output (0: pos < neg, 1: pos > neg)
//
// Notes:
// ------
// - (*) default state
// - Pins used for ADC must be set with PIN_input_AN beforehand. Only the following
//   pins can be used as INPUT for the ADC: PA1, PA2, PC4, PD2, PD3, PD4, PD5, PD6.
// - Pins used as input for OPA comparator must be set with PIN_input_AN beforehand.
//   Only the following pins can be used for the OPA: PA1 or PD0 as negative
//   (inverting) input, PA2 or PD7 as positive (non-inverting) input and PD4 as
//   ouput.
//
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x.h>
#include <debug.h>

// ===================================================================================
// Enumerate PIN designators (use these designators to define pins)
// ===================================================================================
enum{ PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
      PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
      PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7};

// ===================================================================================
// Set PIN as INPUT (high impedance, no pullup/pulldown)
// ===================================================================================
void PIN_input(uint32_t PIN);
#define PIN_input_HI PIN_input
#define PIN_input_FL PIN_input

// ===================================================================================
// Set PIN as INPUT with internal PULLUP resistor
// ===================================================================================
void PIN_input_PU(uint32_t PIN);

// ===================================================================================
// Set PIN as INPUT with internal PULLDOWN resistor
// ===================================================================================
void PIN_input_PD(uint32_t PIN);

// ===================================================================================
// Set PIN as INPUT for analog peripherals (e.g. ADC)
// ===================================================================================
void PIN_input_AN(uint32_t PIN);
#define PIN_input_AD  PIN_input_AN
#define PIN_input_ADC PIN_input_AN

// ===================================================================================
// Set PIN as OUTPUT (push-pull, maximum speed 10MHz)
// ===================================================================================
void PIN_output(uint32_t PIN);
#define PIN_output_PP PIN_output

// ===================================================================================
// Set PIN as OUTPUT OPEN-DRAIN (maximum speed 10MHz)
// ===================================================================================
void PIN_output_OD(uint32_t PIN);

// ===================================================================================
// Set PIN as alternate output (push-pull, maximum speed 10MHz)
// ===================================================================================
void PIN_alternate(uint32_t PIN);
#define PIN_alternate_PP PIN_alternate

// ===================================================================================
// Set PIN as alternate output (open-drain, maximum speed 10MHz)
// ===================================================================================
#define PIN_alternate_OD(PIN) \
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR =  (GPIOA->CFGLR                          \
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))    \
                                           |  ((uint32_t)0b1101<<(((PIN)&7)<<2)) ) : \
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR =  (GPIOC->CFGLR                          \
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))    \
                                           |  ((uint32_t)0b1101<<(((PIN)&7)<<2)) ) : \
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR =  (GPIOD->CFGLR                          \
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))    \
                                           |  ((uint32_t)0b1101<<(((PIN)&7)<<2)) ) : \
(0))))

// ===================================================================================
// Set PIN output value to LOW
// ===================================================================================
void PIN_low(uint32_t PIN);

// ===================================================================================
// Set PIN output value to HIGH
// ===================================================================================
void PIN_high(uint32_t PIN);

// ===================================================================================
// Toggle PIN output value
// ===================================================================================
void PIN_toggle(uint32_t PIN);

// ===================================================================================
// Read PIN input value (returns 0 for LOW, 1 for HIGH)
// ===================================================================================
uint8_t PIN_read(uint32_t PIN);

// ===================================================================================
// Write PIN output value (0 = LOW / 1 = HIGH)
// ===================================================================================
#define PIN_write(PIN, val) (val)?(PIN_high(PIN)):(PIN_low(PIN))

// ===================================================================================
// Enable GPIO PORTS
// ===================================================================================
#define PORTA_enable()      RCC->APB2PCENR |= RCC_IOPAEN;
#define PORTC_enable()      RCC->APB2PCENR |= RCC_IOPCEN;
#define PORTD_enable()      RCC->APB2PCENR |= RCC_IOPDEN;
#define PORTS_enable()      RCC->APB2PCENR |= RCC_IOPAEN | RCC_IOPCEN | RCC_IOPDEN

#define PORT_enable(PIN) \
  ((PIN>=PA0)&&(PIN<=PA7) ? ( RCC->APB2PCENR |= RCC_IOPAEN ) : \
  ((PIN>=PC0)&&(PIN<=PC7) ? ( RCC->APB2PCENR |= RCC_IOPCEN ) : \
  ((PIN>=PD0)&&(PIN<=PD7) ? ( RCC->APB2PCENR |= RCC_IOPDEN ) : \
(0))))

// ===================================================================================
// Disable GPIO PORTS
// ===================================================================================
#define PORTA_disable()     RCC->APB2PCENR &= ~RCC_IOPAEN
#define PORTC_disable()     RCC->APB2PCENR &= ~RCC_IOPCEN
#define PORTD_disable()     RCC->APB2PCENR &= ~RCC_IOPDEN
#define PORTS_disable()     RCC->APB2PCENR &= ~(RCC_IOPAEN | RCC_IOPCEN | RCC_IOPDEN)

#define PORT_disable(PIN) \
  ((PIN>=PA0)&&(PIN<=PA7) ? ( RCC->APB2PCENR &= ~RCC_IOPAEN ) : \
  ((PIN>=PC0)&&(PIN<=PC7) ? ( RCC->APB2PCENR &= ~RCC_IOPCEN ) : \
  ((PIN>=PD0)&&(PIN<=PD7) ? ( RCC->APB2PCENR &= ~RCC_IOPDEN ) : \
(0))))

// ===================================================================================
// ADC Functions
// ===================================================================================
#define ADC_enable()        ADC1->CTLR2  |=  ADC_ADON
#define ADC_disable()       ADC1->CTLR2  &= ~ADC_ADON
#define ADC_fast()          ADC1->SAMPTR2 = 0b00000000000000000000000000000000
#define ADC_slow()          ADC1->SAMPTR2 = 0b00111111111111111111111111111111
#define ADC_medium()        ADC1->SAMPTR2 = 0b00110110110110110110110110110110

#define ADC_input_VREF()    ADC1->RSQR3 = 8
#define ADC_input_VCAL()    ADC1->RSQR3 = 9

void ADC_input(uint32_t PIN);

static inline void ADC_calibrate(void) {
  ADC1->CTLR2 |= ADC_RSTCAL;                    // reset calibration
  while(ADC1->CTLR2 & ADC_RSTCAL);              // wait until finished
  ADC1->CTLR2 |= ADC_CAL;                       // start calibration
  while(ADC1->CTLR2 & ADC_CAL);                 // wait until finished
}

static inline void ADC_init(void) {
  RCC->APB2PCENR |= RCC_ADC1EN | RCC_AFIOEN;    // enable ADC and AFIO
  ADC1->CTLR2 = ADC_ADON | ADC_EXTSEL;          // turn on ADC, software triggering
  delay(1);
  // Delay_Us(10);                                   // wait to settle
  ADC_calibrate();                              // calibrate ADC
}

static inline uint16_t ADC_read(void) {
  ADC1->CTLR2 |= ADC_SWSTART;                   // start conversion
  while(!(ADC1->STATR & ADC_EOC));              // wait until finished
  return ADC1->RDATAR;                          // return result
}

static inline uint16_t ADC_read_VDD(void) {
  ADC_input_VREF();                             // set VREF as ADC input
  return((uint32_t)1200 * 1023 / ADC_read());   // return VDD im mV
}

// ===================================================================================
// OPA Functions
// ===================================================================================
#define OPA_enable()        EXTEN->EXTEN_CTR |=  EXTEN_OPA_EN
#define OPA_disable()       EXTEN->EXTEN_CTR &= ~EXTEN_OPA_EN
#define OPA_read()          ((GPIOD->INDR >> 4) & 1)

#define OPA_negative(PIN) \
  (PIN == PA1 ? (EXTEN->EXTEN_CTR &= ~EXTEN_OPA_NSEL) : \
  (PIN == PD0 ? (EXTEN->EXTEN_CTR |=  EXTEN_OPA_NSEL) : \
(0)))

#define OPA_positive(PIN) \
  (PIN == PA2 ? (EXTEN->EXTEN_CTR &= ~EXTEN_OPA_PSEL) : \
  (PIN == PD7 ? (EXTEN->EXTEN_CTR |=  EXTEN_OPA_PSEL) : \
(0)))

#define OPA_output() {                                           \
  RCC->APB2PCENR |= RCC_AFIOEN;                                  \
  GPIOD->CFGLR    = (GPIOD->CFGLR & ~((uint32_t)0b1111<<(4<<2))) \
                                  |  ((uint32_t)0b1001<<(4<<2)); \
}

#define OPA_output_OD() {                                        \
  RCC->APB2PCENR |= RCC_AFIOEN;                                  \
  GPIOD->CFGLR    = (GPIOD->CFGLR & ~((uint32_t)0b1111<<(4<<2))) \
                                  |  ((uint32_t)0b1101<<(4<<2)); \
}

#define OPA_output_PP       OPA_output

// ===================================================================================
// CMP Functions (alias)
// ===================================================================================
#define CMP_enable          OPA_enable
#define CMP_disable         OPA_disable
#define CMP_read            OPA_read
#define CMP_negative        OPA_negative
#define CMP_positive        OPA_positive
#define CMP_output          OPA_output
#define CMP_output_PP       OPA_output_PP
#define CMP_output_OD       OPA_output_OD

#ifdef __cplusplus
};
#endif
