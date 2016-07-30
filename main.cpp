/*
 * main.c
 */
#include <stdio.h>

#include "Encoder/AMSPositionEncoder.h"
#include "ForceSensor/CurrentForceSensor.h"
#include "MotorDriver/MotorDriver5015a.h"
#include "MainBus/CanBus.h"

#include <string.h>
#include "inc/hw_uart.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"

void InitConsole(void) // Debug logging
{
    // Enable GPIO port A which is used for UART0 pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    // Select the alternate (UART) function for these pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}

void canHandler() {

}


int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);

	// Set up the serial console to use for displaying messages
	InitConsole();

	UARTprintf("Test");



	/*Driver Test Code*/
//	MotorDriver5015a *md = new MotorDriver5015a();
//	md -> setDirection(MotorDriver5015a::CLOCKWISE);
//
//	double speed = 0;
//	long i;
//	while(1) {
//		for(speed = 0;speed < 1; speed += 0.00001) {
//			md -> setSpeed(speed);
//		}
//		md -> emergencyBrake();
//		for(i=0 ; i<1000000 ; i++){}
//		md -> brakeRelease();
//		for(i=0 ; i<1000000 ; i++){}
//		for(; speed>0 ; speed -= 0.00001) {
//			md -> setSpeed(speed);
//		}
//	}



	/* Current Sensor Test code */
//	CurrentForceSensor *cfs = new CurrentForceSensor();
//	double c = cfs -> getCurrent();
//
//	while(1) {
//		c = cfs -> getCurrent();
//	}

	/* Encoder Test Code */
////	char str[15];
//	AMSPositionEncoder *pe = new AMSPositionEncoder();
//	long a = pe -> getPosition();
////	long z = pe -> readZeroPos();
////	uint32_t t1,t2;
////	double time;
////	SysTickPeriodSet(80000000);
////	SysTickEnable();
//	long count =0;
//	while(1) {
////		t1 = SysTickValueGet();
//		a = pe -> getPosition();
//		count++;
////		t2 = SysTickValueGet();
////		time = (t1 - t2);
////		UARTprintf("%u   \r\n", time);
//	}

	/* CAN Test Code */
	CanBus *cb = new CanBus();

	cb -> enableCan();
	cb -> registerInterrupt(canHandler);
	uint32_t data = 1;

	while(1) {
		data ++;
		cb -> sendData(&data);
	}
	return 0;
}

