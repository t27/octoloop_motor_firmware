/*
 * CanBus.h
 *
 *  Created on: 28-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_MAINBUS_CANBUS_H_
#define HALCLASSES_MAINBUS_CANBUS_H_

#include <stdint.h>
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

class CanBus {
public:
	CanBus();
	virtual ~CanBus();
	void registerInterrupt(void (*handler)());
	void enableCan();
	void sendData(unsigned int *message);

private:
	void initCAN();
};

#endif /* HALCLASSES_MAINBUS_CANBUS_H_ */
