/*
 * Params.h
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#ifndef PARAMS_PARAMS_H_
#define PARAMS_PARAMS_H_

#include <stdint.h>
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"

/*
 * Parameter Address definition
 */

#define PARAMS_SIZE 14 // Maximum address value
#define EEPROM_PARAMS_LENGTH 2 // Number of params in EEPROM
#define EEPROM_PARAMS_LENGTH_32BIT 1 //Number of 32bit words needed for the eeprom params
// EEPROM
#define PARAM_FW_VER 0
#define PARAM_ID 1

// RAM
#define PARAM_CURRENT_POSITION_LO 10
#define PARAM_CURRENT_POSITION_HI 11
#define PARAM_TARGET_POSITION_LO 12
#define PARAM_TARGET_POSITION_HI 13


class Params
{
private:
	volatile uint8_t data[20];
//	uint8_t id_; // hex from 0x00 to 0x05
//	uint16_t current_position_; //0-16383
//	uint16_t target_position_; //0-16383
public:

	// Reads the eeprom params from the eeprom and updates, Call only once when the program starts
	void refreshParams() volatile;

	uint8_t getParam(uint8_t address) volatile;
	void setParam(uint8_t address, uint8_t data) volatile;
	void setParam2Byte(uint8_t address, uint16_t value) volatile;
	void setId(uint8_t)  volatile;
	uint8_t getId() volatile;
	void setCurrentPos(uint16_t) volatile; //returns true if set
	uint16_t getCurrentPos() volatile;
	void setTargetPos(uint16_t) volatile; //returns true if set
	uint16_t getTargetPos() volatile;
};

#endif /* PARAMS_PARAMS_H_ */
