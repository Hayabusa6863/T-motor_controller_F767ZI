#include "T_motor_controller.h"

// Constructor
// pass the pointer of CAN_HandleTypeDef as argument
T_motor_controller::T_motor_controller(CAN_HandleTypeDef *hcan_){
	priv_hcan = hcan_;
	pTxHeader.RTR = CAN_RTR_DATA;
	pTxHeader.IDE = CAN_ID_STD;
	pTxHeader.DLC = 8;
	pTxHeader.TransmitGlobalTime = DISABLE;
}


// Register the motor you want to control
HAL_StatusTypeDef T_motor_controller::add_motor(uint8_t can_id_, MotorModel mt_){
	motor.push_back(motor_status(can_id_, mt_));
	motor_id.insert(std::make_pair(can_id_, motor_num));
	motor_num++;
	return HAL_OK;
}


// pack command to CAN_Tx_Message
void T_motor_controller::pack_cmd(motor_status& m){
	pTxHeader.StdId = m.getCanId();
	m.serialize(TxData);
}


// rxdata[0] is the CAN_ID of the motor that send message
// rxdata[1] ~ rxdata[5] is the content of the reply.
void T_motor_controller::unpack_reply(const uint8_t* rxdata){
	motor[motor_id[*rxdata]].deserialize(rxdata+1);
}


void T_motor_controller::setTargetPosition(uint8_t can_id_, float pos_ref_){
	motor[motor_id.at(can_id_)].pos_ref = pos_ref_;
}


void T_motor_controller::setTargetVelocity(uint8_t can_id_, float vel_ref_){
	motor[motor_id.at(can_id_)].vel_ref = vel_ref_;
}


void T_motor_controller::setTargetEffort(uint8_t can_id_, float eff_ref_){
	motor[motor_id.at(can_id_)].eff_ref = eff_ref_;
}


void T_motor_controller::setKp(uint8_t can_id_, float Kp_){
	motor[motor_id.at(can_id_)].Kp = Kp_;
}

void T_motor_controller::setKd(uint8_t can_id_, float Kd_){
	motor[motor_id.at(can_id_)].Kd = Kd_;
}


float T_motor_controller::getPosition(uint8_t can_id_){
	return motor[motor_id.at(can_id_)].pos;
}


float T_motor_controller::getVelocity(uint8_t can_id_){
	return motor[motor_id.at(can_id_)].vel;
}


float T_motor_controller::getEffort(uint8_t can_id_){
	return motor[motor_id.at(can_id_)].eff;
}


// call from timer-ISR to move all registered motor
// In this function...
// 1. convert from integer data to float data in motor_status class
// 2. pack to TxMessage
void T_motor_controller::execute(void){
	if(motor_num == 0){
		// printf("There is no registered motor!\r\n");
	}
	for(auto& e : motor){
		pack_cmd(e);
		HAL_CAN_AddTxMessage(priv_hcan, &pTxHeader, TxData, &TxMailbox);
	}
}
