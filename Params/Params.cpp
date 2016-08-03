/*
 * Params.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#include "Params.h"



uint16_t Params::getCurrentPos()
{
	return currentPos;
}

uint16_t Params::getTargetPos()
{
	return targetPos;
}

uint8_t Params::getId()
{
	return id;
}

void Params::setCurrentPos(uint16_t _currentPos)
{
	currentPos = _currentPos;
}

void Params::setTargetPos(uint16_t _targetPos)
{
	targetPos = _targetPos;
}

void Params::setId(uint8_t _id)
{
	id = _id;
}
