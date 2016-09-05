/*
 * common_funcs.c
 *
 *  Created on: 03-Sep-2016
 *      Author: Tarang
 */

#include "common_funcs.h"


bool checksumValid(uint8_t id, uint8_t length, uint8_t* packet) {
	uint8_t sum = id + length;
	uint8_t i;
	for(i = 0; i < length - 1;i++) {
		sum += packet[i];
	}
	sum = ~(sum);
	if(sum == packet[length-1]) {
		return true;
	} else {
		return false;
	}
}

void UARTInterruptHandler(void)
{
//	cRs485Bus.clearInterrupt();

	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART1_BASE, true); //get interrupt status
	UARTIntClear(UART1_BASE, ui32Status); //clear the asserted interrupts

//	unsigned char packet[20]; //figure out best way of data management

	uint8_t header[2];
	uint8_t i, id, length;
	uint8_t command[10];

//	while(cRs485Bus.charsAvailable()) //loop while there are chars
	while(UARTCharsAvail(UART1_BASE))
	{
		// Read headers
//		cRs485Bus.getData(header, 2); //cRs485Bus.getByte();
		header[0] = UARTCharGetNonBlocking(UART1_BASE);
		header[1] = UARTCharGetNonBlocking(UART1_BASE);

		if (header[0] == 0xff && header[1] == 0xff) {
			// Every transmit should include a TXEN pin HIGH transition
//			cRs485Bus.sendD

			uint8_t ch = 'Y';
			cRs485Bus.sendData(&ch,1);

			id = cRs485Bus.getByte();

			if (id == cParams.getId() || id == cRs485Bus.BROADCAST_ID) {
				length = cRs485Bus.getByte();

				if(length > 10) { // temporary length cap
					//    				return err
				}

				cRs485Bus.getData(command, length);
//				for(i = 0; i < length; i++) {
//					// Length = number of bytes after the length byte including checksum
//					// (Check dynamixel docs)
//					command[i] = UARTCharGetNonBlocking(UART1_BASE);
//				}

				if (checksumValid(id, length, command)) {
					if (command[0] == INSTR_READ_REG) {
						uint8_t add = command[1];
						uint8_t nBytes = command[2];
						if(nBytes > 2) {
							//err
						}
						uint8_t returnData = cParams.getParam(add+i);
						cRs485Bus.sendData(&(returnData), nBytes);
//						for (i = 0; i < nBytes; i++) {
//							// TODO: CREATE A RESPONSE packet here
//
//							UARTCharPutNonBlocking(UART1_BASE, cParams.getParam(add+i));
//						}
					} else if (command[0] == INSTR_WRITE_REG) {
						uint8_t add = command[1];
						// if 1 byte packet = ff,ff,id,len,instr, where,byte,checksum = 8 bytes so len=5
						// for 2 bytes(hi,lo) packet = ff,ff,id,len,instr,where,hi,lo,checksum = 9 bytes, len=5

						if (length == 5) { // more than 1 byte to write
							uint16_t data = command[3]<<8 + command[2];
							cParams.setParam2Byte(add, data);
						} else {
							cParams.setParam(add, command[2]);
						}
					}
				} else {
					uint8_t ch = 'E';
					cRs485Bus.sendData(&ch,1);
				}
			}

		} else {
			UARTCharPutNonBlocking(UART1_BASE, 'X');
		}
	}
}
