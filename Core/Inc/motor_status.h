/**
 * @file	T_motor_controller.h
 * @brief
 * @note	Hayabusa6863
 */

#ifndef MOTOR_STATUS_H_
#define MOTOR_STATUS_H_

#include "stm32f7xx_hal.h"

// available type of motor
enum class MotorModel{
	NOT_SPECIFIED,
	AK10_9,
	AK80_6,
};


// class for data of single motor
class motor_status{
private:
	uint8_t can_id;
	MotorModel motor_type;

	constexpr static uint8_t 	Position_bit_num = 16;
	constexpr static uint8_t	Velocity_bit_num = 12;
	constexpr static uint8_t	Effort_bit_num = 12;
	constexpr static float 		Kp_max = 500.0;
	constexpr static float 		Kp_min = 0.0;
	constexpr static float 		Kd_max = 5.0;
	constexpr static float 		Kd_min = 0.0;

	float P_max, P_min;		// max/min value of Position
	float V_max, V_min;		// max/min value of Velocity
	float T_max, T_min;		// max/min value of Effort

	// Integer raw data
	uint16_t pos_int;
	uint16_t vel_int;
	uint16_t eff_int;

	float pos_ref, pos;
	float vel_ref, vel;
	float eff_ref, eff;

	HAL_StatusTypeDef setParam(MotorModel);
	float uint_to_float(int, float, float, uint8_t);
	int float_to_uint(float, float, float, uint8_t);

public:
	motor_status(void);
	motor_status(uint8_t , MotorModel);
	void deserialize(const uint8_t*);	// copy interger data to this class
	void serialize(uint8_t*);

	void pack_cmd(void);

};

#endif	// motor_status
