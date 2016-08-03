/*
 * Params.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 */

#include "params.h"



uint16_t Params::getCurrentPos()
{
	return current_position_;
}

uint16_t Params::getTargetPos()
{
	return target_position_;
}

uint8_t Params::getId()
{
	return id_;
}

void Params::setCurrentPos(uint16_t currentPosition)
{
	current_position_ = currentPosition;
}

void Params::setTargetPos(uint16_t targetPosition)
{
	target_position_ = targetPosition;
}

void Params::setId(uint8_t id)
{
	id_ = id;
}
