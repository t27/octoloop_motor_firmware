/*
 * MotorDriver.h
 *
 *  Created on: 24-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_MOTORDRIVER_MOTORDRIVER_H_
#define HALCLASSES_MOTORDRIVER_MOTORDRIVER_H_

#include <stdint.h>

class MotorDriver {
public:
	MotorDriver();
	virtual ~MotorDriver();

	enum Direction {
		CLOCKWISE = 0,
		ANTICLOCKWISE = 1
	};

	virtual void setSpeed(float val) = 0;
	virtual void setDirection(Direction d) = 0;
	virtual double getSpeed() = 0;
	virtual Direction getDirection() = 0;
	virtual void emergencyBrake() = 0;

};

#endif /* HALCLASSES_MOTORDRIVER_MOTORDRIVER_H_ */
