/*
This NanoJ Example Code is based on our experience with typical user requirements in a wide range
of industrial applications and is provided without guarantee regarding correctness and completeness.
It serves as general guidance and should not be construed as a commitment of Nanotec to guarantee its
applicability to the customer application without additional tests under the specific conditions
and – if and when necessary – modifications by the customer. 

The responsibility for the applicability and use of the NanoJ Example Code in a particular
customer application lies solely within the authority of the customer.
It is the customer's responsibility to evaluate, investigate and decide,
whether the Example Code is valid and suitable for the respective customer application, or not.
Defects resulting from the improper handling of devices and modules are excluded from the warranty.
Under no circumstances will Nanotec be liable for any direct, indirect, incidental or consequential damages
arising in connection with the Example Code provided. In addition, the regulations regarding the
liability from our Terms and Conditions of Sale and Delivery shall apply.
*/


// The clock-direction mode is set and activated with an input

//1. The modes are mapped in the NanoJ Header
 
 
map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00
map U32 Inputs as input 0x60FD:00
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00
map S08 ModesOfOperationDisplay as input 0x6061:00
map S16 AnalogInput as input 0x3220:01

#include "wrapper.h"
#include "nanotec.h"


//2. Set operation mode


void user()
{
	
	ModesOfOperation(-1);									// set the mode of operation to "clock-direction"
	
	
//3.1 Enable voltage, change the step resolution


	Shutdown();										// set the state machine to "ReadyToSwitchOn"
	
	od_write(0x2057, 0x00, 256);								// set the step resolution to half step per pulse
	
	od_write(0x2058, 0x00, 1);								// step width per pulse = 2057h/2058h
	
	
//3.2 Use input 5 as "enable"


	while(true)
	{
		if(DigitalInput(5))  								// checks whether input 5 is not low
		{	
				EnableOperation();						// set the state machine to "OperationEnabled"
		}
		
		else                								// if input 5 is low
		{	
				Shutdown();							// set the state machine to "ReadyToSwitchOn"
		}

		yield();									// wait for the next cycle (1ms)
	} 
	
}

