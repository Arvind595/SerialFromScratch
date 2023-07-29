/*
This NanoJ Example Code is based on our experience with typical user requirements in a wide range
of industrial applications and is provided without guarantee regarding correctness and completeness.
It serves as general guidance and should not be construed as a commitment of Nanotec to guarantee its
applicability to the customer application without additional tests under the specific conditions
and - if and when necessary - modifications by the customer. 

The responsibility for the applicability and use of the NanoJ Example Code in a particular
customer application lies solely within the authority of the customer.
It is the customer's responsibility to evaluate, investigate and decide,
whether the Example Code is valid and suitable for the respective customer application, or not.
Defects resulting from the improper handling of devices and modules are excluded from the warranty.
Under no circumstances will Nanotec be liable for any direct, indirect, incidental or consequential damages
arising in connection with the Example Code provided. In addition, the regulations regarding the
liability from our Terms and Conditions of Sale and Delivery shall apply.
*/
//This example shows how to use the nanotec.h
//In this example the motor is started in profile position mode and the outputs are set according to certain states
//Digital Input 1 sets the Mode to Profile Position, defines certain behaviours and changes the state to Operation Enabled 
//Digital Input 2 switches between two target positions (1000/3000)
//Digital Input 3 activates a new target position
//Digital Output 1 will be high if target reached has been reached
//Digital Output 2 will be high if the controller ready to switch on
//Digital Output 3 will be high if error occurred

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
 	Out.ProfileVelocity=200;	 		//set the profile velocity to 200rpm
	
	while(true)
	{
	
		if(DigitalInput(1))							//if Input 1 is active
		{		
			ModesOfOperation(1);					//set the Mode to Profile Position		
			EnableOperation();						//change the state to Operation Enabled			
			AbsoluteMovement();						//set to absolute movement
			//RelativeMovement();					//set to relative movement
			ChangeSetPointImmediately(true);		//change setpoint immediately
		}
		else										//else
		{
			Quickstop();							//stop the motor
		}
		
		
		if(DigitalInput(2))							//if Input 2 is active
		{
			Out.TargetPosition=1000;				//set target position to 3000
		}
		else 										//else
		{
			Out.TargetPosition=3000;				//set target position to 3000
		}
	
	
		if(DigitalInput(3))							//if Input 3 is active
		{
			NewSetPoint(true);						//set new setpoint
		}
		else										//else 
		{
			NewSetPoint(false);						//reset new setpoint
		}	
		
		
		if(TargetReached())							//if the target position has been reached	
		{
			SetDigitalOutput(1);					//set output 1
		}
		else										//else														
		{
			ClearDigitalOutput(1);					//clear output 1
		}	
		
		
		if ((In.Statusword & 0xEF) == 0x27) 		//if the "Operation Enabled"-State is reached
		{
			SetDigitalOutput(2);					//set output 1
		}
		else										//else														
		{
			ClearDigitalOutput(2);					//clear output 1
		}		
		
			
		if ((In.Statusword & 0x8) == 0x8) 			//if an error occurs
		{
			SetDigitalOutput(3);					//set output 3
		}
		else										//else														
		{
			ClearDigitalOutput(3);					//clear output 3
		}		
               
		yield();
	}
}
