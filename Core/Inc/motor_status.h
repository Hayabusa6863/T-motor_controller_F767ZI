#ifndef MOTOR_STATUS_H_
#define MOTOR_STATUS_H_

#include "main.h"

// available type of motor
enum class T_motor{
	AK10_9,
	AK80_6,
};


// class for data of single motor
class motor_status{
private:
	uint8_t can_id;
	T_motor motor_type;

	static const float Kp_max = 500.0;
	static const float Kp_min = 0.0;
	static const float Kd_max = 5.0;
	static const float Kd_min = 0.0;

	float P_max, P_min;		// max/min value of Position
	float V_max, V_min;		// max/min value of Velocity
	float T_max, T_min;		// max/min value of Effort

	// Interger raw data
	uint16_t pos_int;
	uint16_t vel_int;
	uint16_t eff_int;


public:
	motor_status();
	motor_status(uint8_t , T_motor);
	void deserialize();	// copy interger data to this class

};

#endif
