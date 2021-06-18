#include "basic_op.h"

float bigger(float x, float y){
	return (x>y) ? x : y;
}

float smaller(float x, float y){
	return (x>y) ? y : x;
}

// conversion from integer to float
float uint_to_float(int x, float x_min, float x_max, uint8_t bits){
	return (x-x_min)*((1<<bits)-1)/(x_max-x_min);
}


// conversion from float to integer
int float_to_uint(float x, float x_min, float x_max, uint8_t bits){
	return ((float)x)*(x_max-x_min) / ((float)((1<<bits)-1)) + x_min;
}
