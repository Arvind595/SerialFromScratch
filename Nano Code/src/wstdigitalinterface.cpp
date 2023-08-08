//Project : WSTTS
//Company : MSPL
//Date : 29-7-2023


//Using Digital Interface of C5-E-11 Motor controller for controlling BLDC motor
//Digital Input		: 	1-5 Open Drain
//Digital Output	: 	1-3	Open Drain
//Analog Input		:	1-2 20mA 
//Analog Output		: 	NULL

#include "wrapper.h"
#include "nanotec.h"

map U16 Controlword				 as inout 	0x6040:00
map U16 Statusword				 as input 	0x6041:00
map U32 Inputs					 as input 	0x60FD:00
map U32 Outputs					 as inout 	0x60FE:01
map S08 ModesOfOperation		 as output 	0x6060:00
map S08 ModesOfOperationDisplay	 as input 	0x6061:00
map S16 AnalogInput				 as input 	0x3220:01
map S32 TargetPosition			 as output 	0x607A:00
map U32	ProfileVelocity			 as output 	0x6081:00
map S32 TargetVelocity			 as inout 	0x60FF:00

map U32	MotorDirection			 as inout	0x205B:00
map U32	BootDelay				 as inout	0x2084:00

/*
	List of Objects: 
	
	~ 1000h Device Type
	~ 1001h Error Register
	~ 1003h Pre-defined Error Field
	~ 1008h Manufacturer Device Name
	~ 1009h Manufacturer Hardware Version
	~ 100Ah Manufacturer Software Version
	~ 1010h Store Parameters
	~ 1011h Restore Default Parameters
	~ 1018h Identity Object
	~ 1020h Verify Configuration
	~ 1F50h Program Data
	~ 1F51h Program Control
	~ 1F57h Program Status
	~ 200Fh IEEE 802 MAC Address
	~ 2010h IP-Configuration
	~ 2011h Static-IPv4-Address
	~ 2012h Static-IPv4-Subnet-Mask
	~ 2013h Static-IPv4-Gateway-Address
	~ 2014h Current-IPv4-Address
	~ 2015h Current-IPv4-Subnet-Mask
	~ 2016h Current-IPv4-Gateway-Address
	~ 2030h Pole Pair Count
	~ 2031h Max Motor Current
	~ 2034h Upper Voltage Warning Level
	~ 2035h Lower Voltage Warning Level
	~ 2036h Open Loop Current Reduction Idle Time
	~ 2037h Open Loop Current Reduction Value/factor
	~ 2038h Brake Controller Timing
	~ 2039h Motor Currents
	~ 203Ah Homing On Block Configuration
	~ 203Bh I2t Parameters
	
	~205Bh Clock Direction Or Clockwise/Counter Clockwise Mode
	~2084h Bootup Delay


	



	Statusword (6041h) 
	xxxx xxxx x0xx 0000 Not ready to switch on
	xxxx xxxx x1xx 0000 Switch on disabled
	xxxx xxxx x01x 0001 Ready to switch on
	xxxx xxxx x01x 0011 Switched on
	xxxx xxxx x01x 0111 Operation enabled
	xxxx xxxx x00x 0111 Quick stop active
	xxxx xxxx x0xx 1111 Fault reaction active
	xxxx xxxx x0xx 1000 Fault


*/

void user(){
		
	BootDelay = 100;
	MotorDirection =0;
	InOut.TargetVelocity = 0;				//start with 0 speed.
	ModesOfOperation(3); 					//what is mode?
	

}