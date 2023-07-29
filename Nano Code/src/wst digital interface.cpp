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

/*
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

	//choose profile Velocity
	InOut.TargetVelocity = 0;				//start with 0 speed.
	ModesOfOperation(3); 					//what is mode?
	

}