/*
This NanoJ Example Code is based on our experience with typical user requirements in a wide range
of industrial applications and is provided without guarantee regarding correctness and completeness.
It serves as general guidance and should not be construed as a commitment of Nanotec to guarantee its
applicability to the customer application without additional tests under the specific conditions
and if and when necessary modifications by the customer. 

The responsibility for the applicability and use of the NanoJ Example Code in a particular
customer application lies solely within the authority of the customer.
It is the customer's responsibility to evaluate, investigate and decide,
whether the Example Code is valid and suitable for the respective customer application, or not.
Defects resulting from the improper handling of devices and modules are excluded from the warranty.
Under no circumstances will Nanotec be liable for any direct, indirect, incidental or consequential damages
arising in connection with the Example Code provided. In addition, the regulations regarding the
liability from our Terms and Conditions of Sale and Delivery shall apply.
*/


//In this example the motor is started in profile position mode
//Digital Input 1 selects the Profile Position Mode, switches to Operation Enabled and selects the behaviour for the Profile Position Mode 
//Digital Input 2 and 3 select the Target Position (0/2000/4000/6000)
//Digital Input 4 activates a new target position
//Digital Input 5 and 6 select the Profile Velocity (100/200/300/500)

map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00
map U32 Inputs as input 0x60FD:00
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00
map S08 ModesOfOperationDisplay as input 0x6061:00
map S16 AnalogInput as input 0x3220:01
map S32 TargetPosition as output 0x607A:00
map U32	ProfileVelocity as output 0x6081:00


#include "wrapper.h"
#include "nanotec.h"


void user()
{
	while(true)
	{
		if(DigitalInput(1))								//if Input 1 is high.
		{	
			ModesOfOperation(1);						//set the Mode to Profile Position			
			EnableOperation();							//change the state to Operation Enabled			
			AbsoluteMovement();							//set to absolute movement
			//RelativeMovement();						//set to relative movement
			ChangeSetPointImmediately(true);			//change setpoint immediately
		}
		else											//else...
		{
			Quickstop();								//stop the motor
		}
		
		// change the Target Position via digital input 2 and 3...		
		if(!DigitalInput(2) & !DigitalInput(3))			//if Input 2 and 3 low 
		{
			Out.TargetPosition=0;					//set the target position to 0
		}		
		else if(DigitalInput(2) & !DigitalInput(3))		//if Input 2 high and 3 low 
		{
			Out.TargetPosition=2000;					//set the target position to 2000
		}
		else if (DigitalInput(3) & !DigitalInput(2))	//if Input 2 low and 3 high 
		{
			Out.TargetPosition=4000;					//set the target position to 4000
		}	
		else if (DigitalInput(3) & DigitalInput(2))		//if Input 2 and 3 high 
		{
			Out.TargetPosition=6000;					//set the target position to 6000
		}
	
		// start a movement to the selected Target Position...
		if(DigitalInput(4))								//if Input 4 is active.
		{
			NewSetPoint(true);							//set new setpoint
		}
		else											//else 
		{
			NewSetPoint(false);							//reset new setpoint
		}	
	
		
		// change the Profile Velocity via digital input 5 and 6...
	   	if(!DigitalInput(5) & !DigitalInput(6))			//if Input 5 and 6 low
        {
        	Out.ProfileVelocity=100; 				 	//set the velocity to 100
        }	
        else if(DigitalInput(5) & !DigitalInput(6)) 	//if Input 5 high and 6 low
        {
        	Out.ProfileVelocity=200; 					//set the velocity to 200
        }
        else if(!DigitalInput(5) & DigitalInput(6))   	//if Input 5 low and 6 high
        {
        	Out.ProfileVelocity=300; 		   			//set the velocity to 300
        }
        else if(DigitalInput(5) & DigitalInput(6))     	//if Input 5 and 6 high
        {
        	Out.ProfileVelocity=500; 					//set the velocity to 500
        }          
		yield();
	}
}
