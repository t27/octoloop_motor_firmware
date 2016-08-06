/*
 * AMSPositionEncoder.h
 *
 *  Created on: 23-Jul-2016
 *      Author: Tarang
 */

// TODO: Hard code the value of SysCtlClockGet(), to save the overheads of a function call.


#ifndef AMSPOSITIONENCODER_H_
#define AMSPOSITIONENCODER_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "a_position_encoder.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"


class AMSPositionEncoder: public PositionEncoder {
public:

	AMSPositionEncoder();
	virtual ~AMSPositionEncoder();

	uint32_t getPosition();
	uint16_t readZeroPos();

private:
	static const uint8_t CHIP_ADDR = 0x40;
	static const uint8_t POSITION_ADDR = 0xFE;
	static const uint8_t ZERO_ADDR = 0x15;
	void InitI2C3();
	uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg);
	uint32_t I2CReceive2Bytes(uint32_t slave_addr, uint8_t reg);
	void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);

};

#endif /* AMSPOSITIONENCODER_H_ */
