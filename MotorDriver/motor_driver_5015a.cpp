/*
 * MotorDriver5015a.cpp
 *
 *  Created on: 24-Jul-2016
 *      Author: Tarang
 */

#include "motor_driver_5015a.h"

/*
 * For a 1kHz frequency pulse
 */

MotorDriver5015a::MotorDriver5015a() {
	// TODO Auto-generated constructor stub

	// Init PWM and GPIO for direction out, brake, speed read etc
	current_speed = 0;
	currentDirection = CLOCKWISE;

	/* Initialise PWM */
	//Configure PWM Clock divide system clock by 64
	SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

	// Enable the peripherals used by this program.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins

	//Configure PF1,PF2,PF3 Pins as PWM
	GPIOPinConfigure(GPIO_PF1_M1PWM5);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

	//Configure PWM Options
	//PWM_GEN_2 Covers M1PWM4 and M1PWM5
	//PWM_GEN_3 Covers M1PWM6 and M1PWM7
	PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

	//Set the Period (expressed in clock ticks)
	// For 1KHz(1ms Period) Clock cycle duration = 1/(16M/64[PWMdividor]) = 64/16M
	// No of cycles for 1kHz = 0.001/clock cycle = 0.001 * 16M / 64 = 250
	// For 80MHz clock 0.001 * 80M / 64 = 1250
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, PWM_PERIOD);

	//Set PWM duty
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, PWM_PERIOD/2);

	// Enable the PWM generator
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);

	// Turn on the Output pins
	PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);

	/* Initialise GPIOs */

	// Set pins 0 and 3 as output, SW controlled.
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

	setDirection(currentDirection);
	setSpeed(current_speed);
}

MotorDriver5015a::~MotorDriver5015a() {
	// TODO Auto-generated destructor stub
}

// Value is a fraction between 0 and 100
void MotorDriver5015a::setSpeed(float val) {
	//Write 1Khz PWM and Change duty cycle
	if (val < 0) {
		val = 0;
	} else if (val > 100) {
		val = 100;
	}
	current_speed = val;
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (int)((val/PWM_INPUT_MAX) * (float)PWM_PERIOD));
}

double MotorDriver5015a::getSpeed() {
	// TODO:Read PWM input from SpeedInput pin
	return current_speed;
}

void MotorDriver5015a::setDirection(Direction dir) {
	// Set Direction GPIO out
	currentDirection = dir;
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, currentDirection << 4);
}

MotorDriver5015a::Direction MotorDriver5015a::getDirection() {
	// Return currentDirection
	return currentDirection;
}

void MotorDriver5015a::emergencyBrake() {
	// Write GPIO out for emergency brake
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0 << 3);
}

void MotorDriver5015a::brakeRelease() {
	// Write GPIO out for emergency brake
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 1 << 3);
}

void MotorDriver5015a::enableMotor() {
	// Write GPIO out for enabling motor
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0 << 5);
}

void MotorDriver5015a::disableMotor() {
	// Write GPIO out for disabling motor
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 1 << 5);
}
