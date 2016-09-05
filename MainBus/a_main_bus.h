/*
 * MainBus.h
 *
 *  Created on: 28-Jul-2016
 *      Author: Tarang
 */

#ifndef HALCLASSES_MAINBUS_MAINBUS_H_
#define HALCLASSES_MAINBUS_MAINBUS_H_

#include <stdint.h>

class MainBus {
public:
	MainBus();
	virtual void sendData(uint8_t *packet, uint8_t length) = 0;
	virtual void registerInterrupt(void (*handler)()) = 0;
	virtual void getData(uint8_t *packet, uint8_t length) = 0;
	virtual ~MainBus();

private:
	virtual void initialise() = 0;

};

#endif /* HALCLASSES_MAINBUS_MAINBUS_H_ */
