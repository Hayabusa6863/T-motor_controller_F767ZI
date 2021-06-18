#ifndef BASIC_OP_H_
#define BASIC_OP_H_

#include "stm32f7xx_hal.h"

float bigger(float x, float y);
float smaller(float x, float y);

float uint_to_float(int, float, float, uint8_t);
int float_to_uint(float, float, float, uint8_t);

#endif
