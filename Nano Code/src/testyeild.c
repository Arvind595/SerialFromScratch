map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00 
map U32 Inputs as input 0x60FD:00 
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00 
map S08 ModesOfOperationDisplay as input 0x6061:00 
map S16 AnalogInput as input 0x3220:01 
map S32 TargetVelocity as inout 0x60FF:00

#in   clude "wrapper.h"
#include "nanotec.h"

//SetDigitalOutput 1 = clockpin
//SetDigitalOutput 2 = datdpin
//SetDigitalOutput 3 = enable

void user()//setup
{
	U08 TXData = 0x12;

	while(true)//loop
	{
		SetDigitalOutput(3);
		for (U08 i = 0; i < 8; i++) {
   			 if ((TXData & 0x80)>>7 == 1) SetDigitalOutput(2);
    		 else ClearDigitalOutput(2);
    		 SetDigitalOutput(1);
    		 ClearDigitalOutput(1);
    		 TXData = TXData << 1;
  		}
  		SetDigitalOutput(2);
  		SetDigitalOutput(3);
	}
	
	
	yield();
}

