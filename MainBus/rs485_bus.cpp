/*
 * rs485_bus.cpp
 *
 *  Created on: 03-Sep-2016
 *      Author: Tarang
 */

#include "rs485_bus.h"

Rs485Bus::Rs485Bus() {
	initialise(115200);
}

Rs485Bus::~Rs485Bus() {
	// TODO Auto-generated destructor stub
}

void Rs485Bus::initialise(uint32_t baud) {

	// Enable Peripheral Clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// Enable pin PB1 for UART1 U1TX
	GPIOPinConfigure(GPIO_PB1_U1TX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);

	// Enable pin PB0 for UART1 U1RX
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

//	// Set PB5 as output for TX ENABLE, SW controlled.
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);

	// Configure the UART for given baud rate and 8-N-1 operation.
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), baud,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE));
}

void Rs485Bus::initialise() {
	initialise(115200);
}

void Rs485Bus::registerInterrupt(void (*handler)()) {
	UARTIntRegister(UART1_BASE, handler);
	IntEnable(INT_UART1); //enable the UART interrupt
	UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
}

void Rs485Bus::sendData(uint8_t *packet, uint8_t length) {
	uint8_t i;
	// Turn GPIO for TXEN on
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 1 << 4);
	for(i = 0; i < length; i++) {
		UARTCharPut(UART1_BASE, packet[i]);
	}
	// Turn OFF TXEN GPIO
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0 << 4);
}

uint8_t Rs485Bus::getByte() {
	return UARTCharGetNonBlocking(UART1_BASE);
}

void Rs485Bus::getData(uint8_t *packet, uint8_t numBytes) {
	uint8_t i;
	for(i = 0; i < numBytes; i++) {
		packet[i] = UARTCharGetNonBlocking(UART1_BASE);
	}
}

bool Rs485Bus::charsAvailable() {
	return UARTCharsAvail(UART1_BASE);
}

void Rs485Bus::clearInterrupt() {
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART1_BASE, true); //get interrupt status
	UARTIntClear(UART1_BASE, ui32Status); //clear the asserted interrupts
}

