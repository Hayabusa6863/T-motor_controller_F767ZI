#include "motor_status.h"

// Constructor without argument
motor_status::motor_status(void){
	this->can_id = 0;
	this->motor_type = MotorModel::NOT_SPECIFIED;

	pos_int = 1<<(Position_bit_num-1);	// set default value (equals to 0)
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


// return own CAN_ID
const uint8_t motor_status::getCanId(void){
	return this->can_id;
}


// convert from 5-byte RxData (except id_data) to each data
void motor_status::deserialize(const uint8_t *rxdata){
	pos_int = (rxdata[0]<<8) | rxdata[1];
	vel_int = (rxdata[2]<<4) | (rxdata[3]>>4);
	eff_int = ((rxdata[3])&0xF) | rxdata[4];

	pos = uint_to_float(pos_int, P_min, P_max, Position_bit_num);
	vel = uint_to_float(vel_int, V_min, V_max, Velocity_bit_num);
	eff = uint_to_float(eff_int, T_min, T_max, Effort_bit_num);
}


//
void motor_status::serialize(uint8_t *txdata){
	pos_ref = smaller(bigger(P_min, pos_ref), P_max);
	vel_ref = smaller(bigger(V_min, vel_ref), V_max);
	eff_ref = smaller(bigger(T_min, eff_ref), T_max);
	Kp 		= smaller(bigger(Kp_min, Kp), Kp_max);
	Kd 		= smaller(bigger(Kd_min, Kd), Kd_max);

	int pos_ref_int = float_to_uint(pos_ref, P_min, P_max, Position_bit_num);
	int vel_ref_int = float_to_uint(vel_ref, V_min, V_max, Velocity_bit_num);
	int eff_ref_int = float_to_uint(eff_ref, T_min, T_max, Effort_bit_num);
	int Kp_int 		= float_to_uint(Kp, Kp_min, Kp_max, Kp_bit_num);
	int Kd_int 		= float_to_uint(Kd, Kd_min, Kd_max, Kd_bit_num);

	txdata[0] = pos_ref_int >> 8;	// Position 8-H
	txdata[1] = pos_ref_int & 0xFF;	// Position 8-L
	txdata[2] = vel_ref_int >> 4;	// Velocity 8-H
	txdata[3] = ((vel_ref_int & 0xF)<<4) | (Kp_int >> 8);	// Velocity 4-L & Kp 4-H
	txdata[4] = Kp_int & 0xFF;		// Kp 8-L
	txdata[5] = Kd_int >> 8;		// Kd 8-H
	txdata[6] = ((Kd_int & 0xF) << 4) | (eff_ref_int >> 8);	// Kd 4-L & Effort 4-H
	txdata[7] = eff_ref_int & 0xFF;	// Effort 8-L
}
