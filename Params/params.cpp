/*
 * Params.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#include "params.h"


void Params::refreshParams() volatile
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
	EEPROMInit();
	uint8_t tempData[EEPROM_PARAMS_LENGTH_32BIT * 4];
//	uint32_t count = (EEPROM_PARAMS_LENGTH * sizeof(uint8_t)) / sizeof(uint32_t) + ((EEPROM_PARAMS_LENGTH % sizeof(uint32_t)) ? 1 : 0);
	EEPROMRead((uint32_t*)tempData, 0x0, EEPROM_PARAMS_LENGTH_32BIT);
	uint8_t i;
	for(i = 0; i < EEPROM_PARAMS_LENGTH; i++) {
		data[i] = tempData[i];
	}
}

uint8_t Params::getParam(uint8_t address) volatile
{
	// Check address limits
	if (address < PARAMS_SIZE)
	{
		return data[address];
	} else
	{
		return 0xFF;
	}

}

void Params::setParam(uint8_t address, uint8_t value) volatile
{
	// Check address limits

	if (address < PARAMS_SIZE) {
		data[address] = value;
		if (address < EEPROM_PARAMS_LENGTH) {
			// If address is a eeprom address, take the 32 bit word(4 byte chunk) which contains the address and write the word to the eeprom
			uint8_t tempData[EEPROM_PARAMS_LENGTH_32BIT]; // Temp storage for the word
			uint8_t i;
			uint8_t startPosition = address & 0xFC; // Start position in the main data array = nearest multiple of 4 lesser than address ie. 4 for add=6,
			for(i = 0; i < EEPROM_PARAMS_LENGTH; i++) {
				tempData[i] = data[startPosition + i];
			}
			EEPROMProgram((uint32_t*)tempData,0x0 + (startPosition>>2),sizeof(uint32_t)); //write the word at startPosition/4 (word addressing)
		}
	}
}

void Params::setParam2Byte(uint8_t address, uint16_t value) volatile
{
	if (address < PARAMS_SIZE) {
		data[address] = value % 0xFF;
		data[address + 1] = (value >> 8) & 0xFF;
		if (address < EEPROM_PARAMS_LENGTH) {
			// If address is a eeprom address, take the 32 bit word(4 byte chunk) which contains the address and write the word to the eeprom
			uint8_t tempData[EEPROM_PARAMS_LENGTH_32BIT]; // Temp storage for the word
			uint8_t i;
			uint8_t startPosition = address & 0xFC; // Start position in the main data array = nearest multiple of 4 lesser than address ie. 4 for add=6,
			for(i = 0; i < EEPROM_PARAMS_LENGTH; i++) {
				tempData[i] = data[startPosition + i];
			}
			EEPROMProgram((uint32_t*)tempData,0x0 + (startPosition>>2),sizeof(uint32_t)); //write the word at startPosition/4 (word addressing)
		}
	}
}

uint16_t Params::getCurrentPos() volatile
{
	uint8_t lowByte = data[PARAM_CURRENT_POSITION_LO];
	uint8_t hiByte = data[PARAM_CURRENT_POSITION_HI] & 0x3F;
	uint16_t current_position = ((uint16_t)hiByte)<<8 + lowByte;
	return current_position;
}

uint16_t Params::getTargetPos() volatile
{
	uint8_t lowByte = data[PARAM_TARGET_POSITION_LO];
	uint8_t hiByte = data[PARAM_TARGET_POSITION_HI];
	uint16_t target_position = (((uint16_t)hiByte) << 8) + lowByte;
	return target_position;
}

uint8_t Params::getId() volatile
{
	return data[PARAM_ID];
}

void Params::setCurrentPos(uint16_t currentPosition) volatile
{
	data[PARAM_CURRENT_POSITION_LO] = currentPosition & 0xFF;
	data[PARAM_CURRENT_POSITION_HI] = (currentPosition >> 8) & 0xFF;
}

void Params::setTargetPos(uint16_t targetPosition) volatile
{
	data[PARAM_TARGET_POSITION_LO] = targetPosition & 0xFF;
	data[PARAM_TARGET_POSITION_HI] = (targetPosition >> 8) & 0xFF;
}

void Params::setId(uint8_t id) volatile
{
	data[PARAM_ID] = id;
}
