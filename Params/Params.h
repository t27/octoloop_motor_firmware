/*
 * Params.h
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#ifndef PARAMS_PARAMS_H_
#define PARAMS_PARAMS_H_

#include <stdint.h>

class Params
{
private:
	uint8_t id; // hex from 0x00 to 0x05
	uint16_t currentPos; //0-16383
	uint16_t targetPos; //0-16383
public:

	void setId(uint8_t);
	uint8_t getId();
	void setCurrentPos(uint16_t); //returns true if set
	uint16_t getCurrentPos();
	void setTargetPos(uint16_t); //returns true if set
	uint16_t getTargetPos();
};

#endif /* PARAMS_PARAMS_H_ */
