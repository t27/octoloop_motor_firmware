/*
 * CurrentForceSensor.cpp
 *
 *  Created on: 25-Jul-2016
 *      Author: Tarang
 */

#include "current_force_sensor.h"

CurrentForceSensor::CurrentForceSensor() {
	// TODO Auto-generated constructor stub

	// Initialise ADC for reading current sensor value
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	//
	// For this example ADC0 is used with AIN0 on port E7.
	// The actual port and pins used may be different on your part, consult
	// the data sheet for more information. GPIO port E needs to be enabled
	// so these pins can be used.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	//
	// Select the analog ADC function for these pins.
	// Consult the data sheet to see which functions are allocated per pin.
	// TODO: change this to select the port/pin you are using.
	//
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

//	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);
	ADCSequenceDisable(ADC0_BASE, 1);

	// Enable the first sample sequencer to capture the value of channel 0 when
	// the processor trigger occurs.
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
	                             ADC_CTL_END);
	//
	// Since sample sequence 3 is now configured, it must be enabled.
	//
	ADCSequenceEnable(ADC0_BASE, 3);

	//
	// Clear the interrupt status flag.  This is done to make sure the
	// interrupt flag is cleared before we sample.
	//
	ADCIntClear(ADC0_BASE, 3);
}

CurrentForceSensor::~CurrentForceSensor() {
	// TODO Auto-generated destructor stub
}

double CurrentForceSensor::getCurrent() {
	uint32_t current;
	// Trigger the sample sequence.
	//
	// Trigger the ADC conversion.
	//
	ADCProcessorTrigger(ADC0_BASE, 3);

	//
	// Wait for conversion to be completed.
	//
	while(!ADCIntStatus(ADC0_BASE, 3, false))
	{
	}

	//
	// Clear the ADC interrupt flag.
	//
	ADCIntClear(ADC0_BASE, 3);

	//
	// Read ADC Value.
	//
	ADCSequenceDataGet(ADC0_BASE, 3, &current);

	return current;
}

double CurrentForceSensor::getTorque() {
	// Read Current Value and convert to Torque
	double current = getCurrent();

	// convert to Torque representation
	double torque = current * 1;

	return torque;
}
