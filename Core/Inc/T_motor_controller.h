#ifndef T_MOTOR_CONTROLLER_H_
#define T_MOTOR_CONTROLLER_H_

#include "motor_status.h"
#include <vector>
class T_motor_controller{
private:
	std::vector<motor_status> motor;

public:
	void add_motor(uint8_t, T_motor);
};

#endif
