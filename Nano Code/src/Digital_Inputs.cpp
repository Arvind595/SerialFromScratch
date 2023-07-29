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
//--------------------------------------------------------------------------------------------------------------

//EXAMPLE PROFILE VELOCITY USING THE DIGITAL INPUTS

// Inputs Defintition: 
// Input 1: Release (type: switch)
// Input 2: Start (type: push button) -> High is start
// Input 3: Stop (type: push button) -> High is stop
// Input 4: direction (type: switch) -> High = negative, Low = positive 
// Input 5 and 6: speed (type: binary-switch) -> 100, 200, 300, 500 rpm speed

// You can map frequently used objects to be able to read or write them
map U16 Controlword as inout 0x6040:00
map U16 Statusword as input 0x6041:00 
map U32 Inputs as input 0x60FD:00 
map U32 Outputs as inout 0x60FE:01
map S08 ModesOfOperation as output 0x6060:00 
map S08 ModesOfOperationDisplay as input 0x6061:00 
map S16 AnalogInput as input 0x3220:01 
map S32 TargetVelocity as inout 0x60FF:00

// Include the definition of NanoJ functions and symbols

#include "wrapper.h"
#include "nanotec.h"

// The user() function is the entry point of the NanoJ program. 
void user()
{
	// Choose Profile Velocity: 
	S32 Velocity = 0;
	ModesOfOperation(3); 
	InOut.TargetVelocity = Velocity; 

	while(true) 
	{
		// Release signal on Input 1
		while(DigitalInput(1))
		{			
			// Start push button on Input 2: 
			if(DigitalInput(2)) 
			{
				//Start Motor: 
				EnableOperation(); 
			} 
			// Stop push button on Input 3: 			
			if(DigitalInput(3)) 
			{
				//Stop Motor: 
				SwitchOn(); 
			} 
			
			// Set the speed depending on the combined status of Input 5 and 6			
			if(!DigitalInput(5) & !DigitalInput(6))			//Input 5 and 6 low
			{
				Velocity = 100; 
			}
			else if(DigitalInput(5) & !DigitalInput(6))		//Input 5 high and 6 low
			{
				Velocity = 200; 
			}
			else if(!DigitalInput(5) & DigitalInput(6))		//Input 5 low and 6 high
			{
				Velocity = 300; 
			}
			else if(DigitalInput(5) & DigitalInput(6))		//Input 5 and 6 high
			{
				Velocity = 500; 
			}			
			
			// Change Direction with Input 4: 
			if(DigitalInput(4)) 
			{
				InOut.TargetVelocity = - Velocity; 	
			}
			else
			{
				InOut.TargetVelocity = Velocity; 	
			}
			yield(); 	
		}
		
		// If Release signal is low 
		Shutdown(); 
		yield();
	}
}
