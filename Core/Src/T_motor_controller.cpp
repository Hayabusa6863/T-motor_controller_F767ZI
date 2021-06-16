#include "T_motor_controller.h"

// Constructor with argument
T_motor_controller::T_motor_controller(CAN_HandleTypeDef *hcan_){
	priv_hcan = hcan_;
}


HAL_StatusTypeDef T_motor_controller::add_motor(uint8_t can_id_, MotorModel mt_){
	motor.push_back(motor_status(can_id_, mt_));
	return HAL_OK;
}


// call from timer-ISR to move motor
// In this function...
// 1. convert from integer data to float data in motor_status class
// 2. pack to TxMessage
void T_motor_controller::execute(void){

}
