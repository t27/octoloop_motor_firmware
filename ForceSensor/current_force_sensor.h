/*
 * CurrentForceSensor.h
 *
 *  Created on: 25-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_FORCESENSOR_CURRENTFORCESENSOR_H_
#define HALCLASSES_FORCESENSOR_CURRENTFORCESENSOR_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "a_force_sensor.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"


class CurrentForceSensor: public ForceSensor {
public:
	CurrentForceSensor();
	virtual ~CurrentForceSensor();
	double getTorque();
	double getCurrent();
};

#endif /* HALCLASSES_FORCESENSOR_CURRENTFORCESENSOR_H_ */
