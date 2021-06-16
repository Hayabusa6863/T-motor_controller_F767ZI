#include "motor_status.h"

// Constructor without argument
motor_status::motor_status(void){
	this->can_id = 0;
	this->motor_type = MotorModel::NOT_SPECIFIED;

	pos_int = 1<<(Position_bit_num-1);
	vel_int = 1<<(Velocity_bit_num-1);
	eff_int = 1<<(Effort_bit_num-1);
}


// Constructor with argument
motor_status::motor_status(uint8_t id_, MotorModel mt){
	this->can_id = id_;
	this->motor_type = mt;

	pos_int = 1<<(Position_bit_num-1);
	vel_int = 1<<(Velocity_bit_num-1);
	eff_int = 1<<(Effort_bit_num-1);

	setParam(mt);
}


// Set parameters according to motor type
HAL_StatusTypeDef motor_status::setParam(MotorModel mt){
	switch(mt){
	case MotorModel::AK10_9:
		P_max = 12.5;
		P_min = -12.5;
		V_max = 46.57;
		V_min = -46.57;
		T_max = 18.0;
		T_min = -18.0;
		return HAL_OK;

	case MotorModel::AK80_6:
		P_max = 12.5;
		P_min = -12.5;
		V_max = 38.2;
		V_min = -38.2;
		T_max = 12.0;
		T_min = -12.0;
		return HAL_OK;

	default:
		return HAL_ERROR;
	}
}

// conversion from integer to float
float motor_status::uint_to_float(int x, float x_min, float x_max, uint8_t bits){
	return (x-x_min)*((1<<bits)-1)/(x_max-x_min);
}


// conversion from float to integer
int float_to_uint(float x, float x_min, float x_max, uint8_t bits){
	return ((float)x)*(x_max-x_min) / ((float)((1<<bits)-1)) + x_min;
}


// convert from 5-byte RxData (except id_data) to each data
void motor_status::deserialize(const uint8_t *rxdata){
	pos_int = (rxdata[0]<<8) | rxdata[1];
	vel_int = (rxdata[2]<<4) | (rxdata[3]>>4);
	eff_int = ((rxdata[3])&0xF) | rxdata[4];
}



void serialize(uint8_t *txdata){

}
