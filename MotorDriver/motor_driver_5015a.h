/*
 * MotorDriver5015a.h
 *
 *  Created on: 24-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_MOTORDRIVER_MOTORDRIVER5015A_H_
#define HALCLASSES_MOTORDRIVER_MOTORDRIVER5015A_H_

#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "a_motor_driver.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"


#define PWM_PERIOD 80000 //In clock ticks
#define PWM_INPUT_MAX 100

class MotorDriver5015a: public MotorDriver {
public:
	MotorDriver5015a();
	virtual ~MotorDriver5015a();

	void setSpeed(float val);
	double getSpeed();
	void setDirection(Direction d);
	Direction getDirection();
	void emergencyBrake();
	void brakeRelease();
	void enableMotor();
	void disableMotor();
private:
	double current_speed;
	Direction currentDirection;
};

#endif /* HALCLASSES_MOTORDRIVER_MOTORDRIVER5015A_H_ */
