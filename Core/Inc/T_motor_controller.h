/**
 * @file	T_motor_controller.h
 * @brief
 * @note	Hayabusa6863
 */

#ifndef T_MOTOR_CONTROLLER_H_
#define T_MOTOR_CONTROLLER_H_

#include "motor_status.h"
#include <vector>
class T_motor_controller{
private:
	CAN_HandleTypeDef *priv_hcan;
	void pack_cmd(CAN_TxHeaderTypeDef*);

public:
	std::vector<motor_status> motor;

	T_motor_controller(CAN_HandleTypeDef*);
	HAL_StatusTypeDef add_motor(uint8_t, MotorModel);
	void unpack_reply(CAN_RxHeaderTypeDef*);
	void execute(void);	// control all motor
};

#endif	// T_motor_controller
