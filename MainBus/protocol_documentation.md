# Motor Communication Protocol

## About

The motor Communication protocol is very similar to the dynamixel protocol. There is a difference in register addresses only.

## Protocol description

Byte based protocol.

#### Transmit Data to motor protocol

The protocol for sending data to a motor

First 2 bytes - **Header** - `0xFF 0xFF`

3rd Byte - **Id** - possible values from `0x00` to `0xFD`, Broadcast ID = `0xFE`

4th Byte - **Length** - Length(in number of bytes) of the whole packet not counting the *Header* and *Id* bytes

5th Byte - **Instruction** - The instruction for the motor. Can be any of the values mentioned [here](#instructions)

6th Byte and beyond - **Parameters for the instruction** - As defined [here](#instructions)

Last Byte = Checksum = Logical Not of the 8bit sum of all bits of the packet except the header. `= ~( sum(packet[2], ... ,packet[last]) & 0xFF)`

#### Receive packet from motor

**TBD**

## Instructions

`0x01` - **PING** - No execution - It is used when controller is ready to receive Status Packet

`0x02` - **READ_DATA** - This command reads data from the motor.

*READ DATA Parameters* = **2 Bytes**; Where and How many. First byte is the address of the location to be read. Seconf byte is the number of bytes to be read from the location(=1 normally, =2 in case of 2 byte data)

`0x03` - **WRITE_DATA** - This command writes data to the motor

*WRITE DATA Parameters* = **2 or 3 bytes**; Where and what. First byte is address where the data is to be written, Second byte is the value to be written. If the data is of 2 bytes, then the Low Byte and High byte are sent.

For 1 byte data, Params = Address, Byte data

For 2 byte data, Params = Address, Low Byte, High Byte

`0x04` - **REG WRITE** - It is similar to WRITE_DATA, but it remains in the standby state without being executed until the ACTION command arrives. *TBD*

`0x05` - **ACTION** - This command initiates motions registered with REG WRITE *TBD*

`0x06` - **RESET** - This command restores the state of the motor to the factory default setting.	*TBD*

`0x83` - **SYNC WRITE** - *TODO* This command is used to control several motors simultaneously at a time.
