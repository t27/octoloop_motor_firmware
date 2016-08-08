/*
 * temp_arduino.h
 *
 *  Created on: Aug 8, 2016
 *      Author: Kaustubh
 */

#ifndef TEMPARDUINO_TEMP_ARDUINO_H_
#define TEMPARDUINO_TEMP_ARDUINO_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/uart.h"

class TempArduino {
private:
	void uartInit();

public:
	TempArduino();
	~TempArduino();
	uint16_t getPositionEncoderPosition();
	uint16_t getLoadEncoderPosition();
};

#endif /* TEMPARDUINO_TEMP_ARDUINO_H_ */
