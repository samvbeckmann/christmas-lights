#include <stdint.h>

#ifndef CHRISTMAS_LIGHTS_LPD8806LIB_H
#define CHRISTMAS_LIGHTS_LPD8806LIB_H

#define DATA_PIN GPIO_PIN_0
#define CLOCK_PIN GPIO_PIN_1

void initLEDStrip(void);
void showStrip(void);
void setRGB( uint16_t idx, uint8_t r, uint8_t g, uint8_t b );

#endif
