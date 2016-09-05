/*
 * rs485_bus.h
 *
 *  Created on: 03-Sep-2016
 *      Author: Tarang
 */

#ifndef MAINBUS_RS485_BUS_H_
#define MAINBUS_RS485_BUS_H_

//#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

#include "a_main_bus.h"

#define INSTR_PING 0x01
#define INSTR_READ_REG 0x02
#define INSTR_WRITE_REG 0x03
#define INSTR_WRITE_QUEUE 0x04
#define INSTR_QUEUE_ACTION 0x05
#define INSTR_FACTORY_RESET 0x06
#define INSTR_SYNC_WRITE 0x83

class Rs485Bus: public MainBus {
public:
	Rs485Bus();
	virtual ~Rs485Bus();
	void sendData(uint8_t *packet, uint8_t length);
	void registerInterrupt(void (*handler)());
	uint8_t getByte();
	void getData(uint8_t *packet, uint8_t numBytes);
	void clearInterrupt();
	bool charsAvailable();

	const uint8_t BROADCAST_ID = 0xFE;

private:
	void initialise();
	void initialise(uint32_t baud);
};

#endif /* MAINBUS_RS485_BUS_H_ */
