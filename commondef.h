/*
 * commondef.h
 *
 *  Created on: Jul 31, 2016
 *      Author: Kaustubh
 *      Contains all header files, definitions
 */

#ifndef COMMONDEF_H_
#define COMMONDEF_H_

/*
 *
 int8_t		uint8_t  (0 to 255)								byte
 int16_t	uint16_t (0 to 65,535)							short
 int32_t	uint32_t (0 to 4,294,967,295)					int
 int64_t	uint64_t (0 to 18,446,744,073,709, 551,615)		long
 */


#include <stdio.h>
#include <stdint.h>

#include "Encoder/AMSPositionEncoder.h"
#include "ForceSensor/CurrentForceSensor.h"
#include "MotorDriver/MotorDriver5015a.h"
#include "MainBus/CanBus.h"


#include "inc/hw_uart.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"







#endif /* COMMONDEF_H_ */
