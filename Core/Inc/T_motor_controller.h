/**
 * @file	T_motor_controller.h
 * @brief
 * @note	Hayabusa6863
 */

#ifndef T_MOTOR_CONTROLLER_H_
#define T_MOTOR_CONTROLLER_H_

#include "motor_status.h"
#include <vector>
#include <map>
class T_motor_controller{
private:
	CAN_HandleTypeDef *priv_hcan;
	CAN_TxHeaderTypeDef pTxHeader;
	uint8_t TxData[8];
	uint32_t TxMailbox;

	std::vector<motor_status> motor;
	std::map<uint8_t, uint8_t> motor_id;	// the pair of CAN_ID and Index of vector
	uint8_t motor_num = 0;

	void pack_cmd(motor_status&);
public:
	T_motor_controller(CAN_HandleTypeDef*);

	HAL_StatusTypeDef add_motor(uint8_t, MotorModel);
	void unpack_reply(const uint8_t*);

	// setter
	/* Warning: Please pass the CAN_ID as the argument !*/
	void setTargetPosition(uint8_t can_id, float pos_ref);
	void setTargetVelocity(uint8_t can_id, float vel_ref);
	void setTargetEffort(uint8_t can_id, float eff_ref);
	void setKp(uint8_t can_id, float Kp);
	void setKd(uint8_t can_id, float Kd);

	// getter
	/* Warning: Please pass the CAN_ID as the argument !*/
	float getPosition(uint8_t can_id);
	float getVelocity(uint8_t can_id);
	float getEffort(uint8_t can_id);

	void execute(void);	// control all registered motor
};

#endif	// T_motor_controller
