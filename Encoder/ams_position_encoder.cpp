/*
 * AMSPositionEncoder.cpp
 *
 *  Created on: 23-Jul-2016
 *      Author: Tarang
 */
#include "ams_position_encoder.h"

AMSPositionEncoder::AMSPositionEncoder() {
	InitI2C3();
}

AMSPositionEncoder::~AMSPositionEncoder() {
}

uint32_t AMSPositionEncoder::getPosition() {
	uint32_t positionLSB = I2CReceive(CHIP_ADDR, POSITION_ADDR);
	uint32_t positionMSB = I2CReceive(CHIP_ADDR, POSITION_ADDR + 1);

	uint32_t position = ((positionMSB & 0x3F)<<8) + positionLSB;

	//	long position = I2CReceive2Bytes(CHIP_ADDR, POSITION_ADDR);
	return position;
}

uint16_t AMSPositionEncoder::readZeroPos() {
	uint16_t positionMSB = I2CReceive(CHIP_ADDR, ZERO_ADDR);
	uint16_t positionLSB = I2CReceive(CHIP_ADDR, ZERO_ADDR + 1);

	uint16_t position = (positionMSB<<8) + positionLSB;

	return position;
}
void AMSPositionEncoder::InitI2C3(void) {

	//enable peripheral clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	//Enable pin PD1 for I2C3 I2C3SDA
	GPIOPinConfigure(GPIO_PD1_I2C3SDA);
	GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

	//Enable pin PD0 for I2C3 I2C3SCL
	GPIOPinConfigure(GPIO_PD0_I2C3SCL);
	GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);

	// Enable and initialize the I2C3 master module.  Use the system clock for
	// the I2C3 module.  The last parameter sets the I2C data transfer rate.
	// If false: 100kbps; true: 400kbps.

	I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), false);

	//clear I2C FIFOs
	HWREG(I2C3_BASE + I2C_O_FIFOCTL) = 80008000;
}

//read specified register on slave device
uint32_t AMSPositionEncoder::I2CReceive(uint32_t slave_addr, uint8_t reg)
{
	//specify that we are writing (a register address) to the
	//slave device
	I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);

	//specify register to be read
	I2CMasterDataPut(I2C3_BASE, reg);

	//send control byte and register address byte to slave device
	I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);

	//wait for MCU to finish transaction
	while(I2CMasterBusy(I2C3_BASE));


	//specify that we are going to read from slave device
	I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, true);
	//send control byte and read from the register we
	//specified
	I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
	//wait for MCU to finish transaction
	while(I2CMasterBusy(I2C3_BASE));

	//return data pulled from the specified register
	return I2CMasterDataGet(I2C3_BASE);
}

uint32_t AMSPositionEncoder::I2CReceive2Bytes(uint32_t slave_addr, uint8_t reg)
{
	//specify that we are writing (a register address) to the
	//slave device
	I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);

	//specify register to be read
	I2CMasterDataPut(I2C3_BASE, reg);

	//send control byte and register address byte to slave device
	I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);

	//wait for MCU to finish transaction
	while (!(I2CMasterBusy(I2C3_BASE))); //Wait till end of transaction

	while (I2CMasterBusy(I2C3_BASE)); //Wait till end of transaction

	//specify that we are going to read from slave device
	I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, true);

	I2CMasterControl (I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); //Read the 1st Byte

	while (!(I2CMasterBusy(I2C3_BASE))); //Wait till end of transaction

	while (I2CMasterBusy(I2C3_BASE)); //Wait till end of transaction

	unsigned char B1 = (uint8_t)(I2CMasterDataGet (I2C3_BASE)); //Read from FIFO

	while (!(I2CMasterBusy(I2C3_BASE))); //Wait till end of transaction

	while (I2CMasterBusy(I2C3_BASE)); //Wait till end of transaction

	I2CMasterControl (I2C3_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); //Read the 2nd Byte

	unsigned char B2 = (uint8_t)(I2CMasterDataGet (I2C3_BASE)); //Read from FIFO

	//return data pulled from the specified register
	return (B1<<8) + B2;
}

//sends an I2C command to the specified slave
void AMSPositionEncoder::I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
	// Tell the master module what address it will place on the bus when
	// communicating with the slave.
	I2CMasterSlaveAddrSet(I2C3_BASE, slave_addr, false);

	//stores list of variable number of arguments
	va_list vargs;

	//specifies the va_list to "open" and the last fixed argument
	//so vargs knows where to start looking
	va_start(vargs, num_of_args);

	//put data to be sent into FIFO
	I2CMasterDataPut(I2C3_BASE, va_arg(vargs, uint32_t));

	//if there is only one argument, we only need to use the
	//single send I2C function
	if(num_of_args == 1)
	{
		//Initiate send of data from the MCU
		I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);

		// Wait until MCU is done transferring.
		while(I2CMasterBusy(I2C3_BASE));

		//"close" variable argument list
		va_end(vargs);
	}

	//otherwise, we start transmission of multiple bytes on the
	//I2C bus
	else
	{
		//Initiate send of data from the MCU
		I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);

		// Wait until MCU is done transferring.
		while(I2CMasterBusy(I2C3_BASE));

		//send num_of_args-2 pieces of data, using the
		//BURST_SEND_CONT command of the I2C module
		for(uint8_t i = 1; i < (num_of_args - 1); i++)
		{
			//put next piece of data into I2C FIFO
			I2CMasterDataPut(I2C3_BASE, va_arg(vargs, uint32_t));
			//send next data that was just placed into FIFO
			I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

			// Wait until MCU is done transferring.
			while(I2CMasterBusy(I2C3_BASE));
		}

		//put last piece of data into I2C FIFO
		I2CMasterDataPut(I2C3_BASE, va_arg(vargs, uint32_t));
		//send next data that was just placed into FIFO
		I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
		// Wait until MCU is done transferring.
		while(I2CMasterBusy(I2C3_BASE));

		//"close" variable args list
		va_end(vargs);
	}
}
