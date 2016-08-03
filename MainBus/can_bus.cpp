/*
 * CanBus.cpp
 *
 *  Created on: 28-Jul-2016
 *      Author: Tarang
 */

#include "can_bus.h"

CanBus::CanBus() {
	initCAN();

}

CanBus::~CanBus() {
	// TODO Auto-generated destructor stub
}

void CanBus::initCAN() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinConfigure(GPIO_PE4_CAN0RX);
	GPIOPinConfigure(GPIO_PE5_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	CANInit(CAN0_BASE);
	CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
}

void CanBus::registerInterrupt(void (*handler)()) {
	CANIntRegister(CAN0_BASE, handler); // use dynamic vector table allocation
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
	IntEnable(INT_CAN0);
}

void CanBus::enableCAN() {
	CANEnable(CAN0_BASE);
}

void CanBus:: sendData(unsigned int *message) {
	//can message object
	tCANMsgObject msg; // the CAN message object
//	unsigned int msgData; // the message data is four bytes long which we can allocate as an int32
	uint8_t *msgDataPtr = (uint8_t *)message; // make a pointer to msgData so we can access individual bytes

	//setup message object
	msg.ui32MsgID = 1;
	msg.ui32MsgIDMask = 0;
	msg.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
	msg.ui32MsgLen = sizeof(msgDataPtr);
	msg.pui8MsgData = msgDataPtr;


    CANMessageSet(CAN0_BASE, 1, &msg, MSG_OBJ_TYPE_TX);
}

