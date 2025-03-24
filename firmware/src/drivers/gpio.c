#include "gpio.h"

void PIN_input(uint32_t PIN) {

  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR =  (GPIOA->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0100<<(((PIN)&7)<<2)) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR =  (GPIOC->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0100<<(((PIN)&7)<<2)) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR =  (GPIOD->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0100<<(((PIN)&7)<<2)) ) :
    (0))));
}

void PIN_input_PU(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ({GPIOA->CFGLR  =  (GPIOA->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOA->BSHR   =  ((uint32_t)1<<((PIN)&7));        }) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ({GPIOC->CFGLR  =  (GPIOC->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOC->BSHR   =  ((uint32_t)1<<((PIN)&7));        }) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ({GPIOD->CFGLR  =  (GPIOD->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOD->BSHR   =  ((uint32_t)1<<((PIN)&7));        }) :
(0))));
}

void PIN_input_PD(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ({GPIOA->CFGLR  =  (GPIOA->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOA->BCR    =  ((uint32_t)1<<((PIN)&7));        }) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ({GPIOC->CFGLR  =  (GPIOC->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOC->BCR    =  ((uint32_t)1<<((PIN)&7));        }) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ({GPIOD->CFGLR  =  (GPIOD->CFGLR
                                            & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                            |  ((uint32_t)0b1000<<(((PIN)&7)<<2));
                              GPIOD->BCR    =  ((uint32_t)1<<((PIN)&7));        }) :
(0))));
}

void PIN_input_AN(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR &= ~((uint32_t)0b1111<<(((PIN)&7)<<2)) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR &= ~((uint32_t)0b1111<<(((PIN)&7)<<2)) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR &= ~((uint32_t)0b1111<<(((PIN)&7)<<2)) ) :
(0))));
}

void PIN_output(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR =  (GPIOA->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0001<<(((PIN)&7)<<2)) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR =  (GPIOC->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0001<<(((PIN)&7)<<2)) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR =  (GPIOD->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0001<<(((PIN)&7)<<2)) ) :
(0))));
}

void PIN_output_OD(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR =  (GPIOA->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0101<<(((PIN)&7)<<2)) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR =  (GPIOC->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0101<<(((PIN)&7)<<2)) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR =  (GPIOD->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b0101<<(((PIN)&7)<<2)) ) :
(0))));
}

void PIN_alternate(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->CFGLR =  (GPIOA->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b1001<<(((PIN)&7)<<2)) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->CFGLR =  (GPIOC->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b1001<<(((PIN)&7)<<2)) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->CFGLR =  (GPIOD->CFGLR
                                           & ~((uint32_t)0b1111<<(((PIN)&7)<<2)))
                                           |  ((uint32_t)0b1001<<(((PIN)&7)<<2)) ) :
(0))));
}

void PIN_low(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->BCR = 1<<((PIN)&7) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->BCR = 1<<((PIN)&7) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->BCR = 1<<((PIN)&7) ) :
(0))));
}

void PIN_high(uint32_t PIN) {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->BSHR = 1<<((PIN)&7) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->BSHR = 1<<((PIN)&7) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->BSHR = 1<<((PIN)&7) ) :
(0))));
}

void PIN_toggle(uint32_t PIN)  {
  ((PIN>=PA0)&&(PIN<=PA7) ? ( GPIOA->OUTDR ^= 1<<((PIN)&7) ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( GPIOC->OUTDR ^= 1<<((PIN)&7) ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( GPIOD->OUTDR ^= 1<<((PIN)&7) ) :
(0))));
}

uint8_t PIN_read(uint32_t PIN) {
    return
  ((PIN>=PA0)&&(PIN<=PA7) ? ( (GPIOA->INDR>>((PIN)&7))&1 ) :
  ((PIN>=PC0)&&(PIN<=PC7) ? ( (GPIOC->INDR>>((PIN)&7))&1 ) :
  ((PIN>=PD0)&&(PIN<=PD7) ? ( (GPIOD->INDR>>((PIN)&7))&1 ) :
(0))));
}

void ADC_input(uint32_t PIN) {
  (PIN == PA1 ? (ADC1->RSQR3 = 1) :
  (PIN == PA2 ? (ADC1->RSQR3 = 0) :
  (PIN == PC4 ? (ADC1->RSQR3 = 2) :
  (PIN == PD2 ? (ADC1->RSQR3 = 3) :
  (PIN == PD3 ? (ADC1->RSQR3 = 4) :
  (PIN == PD4 ? (ADC1->RSQR3 = 7) :
  (PIN == PD5 ? (ADC1->RSQR3 = 5) :
  (PIN == PD6 ? (ADC1->RSQR3 = 6) :
(0)))))))));
}