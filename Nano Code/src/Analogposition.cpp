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
//In this example the motor is started in profile position mode. The Target Position is set via the analog input
//The analog input scales the voltage-range to 0-1023, this also gives the resolution of the analog input

map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00
map U32 Inputs as input 0x60FD:00
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00
map S08 ModesOfOperationDisplay as input 0x6061:00
map S16 AnalogInput as input 0x3220:01
map S32 TargetPosition as output 0x607A:00
map U32	ProfileVelocity as output 0x6081:00
map S16 TargetVelocity as output 0x6042:00

#include "wrapper.h"
#include "nanotec.h"

void user()
{
	od_write(0x2300, 0x00, 5);										//Autoyield
	Out.ProfileVelocity=100; 										//Sets the velocity 100
	S32 Position=360;												//defines the Target Position when the analog input is at its max. value
	S32 NewAnalog = 0;												//defines a new variable 
	S32 OldAnalog = 0;												//defines a new variable 
	S32 Play = 10;													//filter for the analog input

	ModesOfOperation(1);											//set the Mode to Profile Position 
	AbsoluteMovement(); 											//absolute movement
	EnableOperation();												//changes the state to Operation Enabled
	ChangeSetPointImmediately(true);								//this allowes the controller to change the target immediately

	while(true)
	{		
		NewAnalog =	AnalogInput();  								//sets the variable NewAnalog to the value of the analog signal
		
		if(NewAnalog > OldAnalog+Play || NewAnalog < OldAnalog-Play)//checks if the change at the analog input is higher then the defined play
		{
			Out.TargetPosition = NewAnalog * Position/1024;  		//calculates the new Target Position
			OldAnalog = NewAnalog;									//safes the last change to the variable Oldanalog
		}
		
		if(NewSetPointAcknowledge())								//activtes a newly given Target Position
		{
		 	NewSetPoint(false);
		}
		else
		{
			NewSetPoint(true);
		}  
		   
	    yield(); 
	 }		
}
