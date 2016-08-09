/*
 * temp_arduino.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: Kaustubh
 */

#include "temp_arduino.h"

TempArduino::TempArduino() {
	uartInit();
}

TempArduino::~TempArduino() {
}

void TempArduino::uartInit() {
	//
	// Enable Peripheral Clocks
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	//
	// Enable pin PB1 for UART1 U1TX
	//
	GPIOPinConfigure(GPIO_PB1_U1TX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);

	//
	// Enable pin PB0 for UART1 U1RX
	//
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

	//
	// Configure the UART for 115200, 8-N-1 operation.
	//
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 1000000,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE));
}


//
// Send the charecter 'p' and then wait for the Arduino
// to send the postion encoder postion back
//
uint16_t TempArduino::getPositionEncoderPosition() {
	UARTCharPut(UART1_BASE, 'p');
	uint8_t LSB = UARTCharGet(UART1_BASE);
	uint8_t MSB = UARTCharGet(UART1_BASE);
	return (((MSB & 0x3F) << 8)|LSB);
}

//
// Send the charecter 'l' and then wait for the Arduino
// to send the load encoder position back
//
uint16_t TempArduino::getLoadEncoderPosition(){
	UARTCharPut(UART1_BASE, 'l');
	uint8_t LSB = UARTCharGet(UART1_BASE);
	uint8_t MSB = UARTCharGet(UART1_BASE);
	return (((MSB & 0x3F) << 8)|LSB);
}





