/*
 * PositionEncoder.h
 *
 *  Created on: 23-Jul-2016
 *      Author: Tarang
 */

#ifndef POSITIONENCODER_H_
#define POSITIONENCODER_H_

class PositionEncoder {
public:
	PositionEncoder();
	virtual ~PositionEncoder();

	virtual int getPosition() = 0;
};

#endif /* POSITIONENCODER_H_ */
