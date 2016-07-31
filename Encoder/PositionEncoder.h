/*
 * PositionEncoder.h
 *
 *  Created on: 23-Jul-2016
 *      Author: Tarang
 */

#ifndef POSITIONENCODER_H_
#define POSITIONENCODER_H_

#include <stdint.h>

class PositionEncoder {
public:
	PositionEncoder();
	virtual ~PositionEncoder();

	virtual uint16_t getPosition() = 0;
};

#endif /* POSITIONENCODER_H_ */
