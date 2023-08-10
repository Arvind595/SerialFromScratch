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
map U32 Inputs					 as input 	0x2400:00
map U32 Outputs					 as inout 	0x2500:01
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


		1000H DEVICE TYPE
		1001H ERROR REGISTER
		1003H PRE-DEFINED ERROR FIELD
		1005H COB-ID SYNC
		1006H COMMUNICATION CYCLE PERIOD
		1007H SYNCHRONOUS WINDOW LENGTH
		1008H MANUFACTURER DEVICE NAME
		1009H MANUFACTURER HARDWARE VERSION
		100AH MANUFACTURER SOFTWARE VERSION
		100CH GUARD TIME
		100DH LIVE TIME FACTOR
		1010H STORE PARAMETERS
		1011H RESTORE DEFAULT PARAMETERS
		1014H COB-ID EMCY
		1016H CONSUMER HEARTBEAT TIME
		1017H PRODUCER HEARTBEAT TIME
		1018H IDENTITY OBJECT
		1019H SYNCHRONOUS COUNTER OVERFLOW VALUE
		1020H VERIFY CONFIGURATION
		1029H ERROR BEHAVIOR
		1400H RECEIVE PDO 1 COMMUNICATION PARAMETER
		1401H RECEIVE PDO 2 COMMUNICATION PARAMETER
		1402H RECEIVE PDO 3 COMMUNICATION PARAMETER
		1403H RECEIVE PDO 4 COMMUNICATION PARAMETER
		1404H RECEIVE PDO 5 COMMUNICATION PARAMETER
		1405H RECEIVE PDO 6 COMMUNICATION PARAMETER
		1406H RECEIVE PDO 7 COMMUNICATION PARAMETER
		1407H RECEIVE PDO 8 COMMUNICATION PARAMETER
		1600H RECEIVE PDO 1 MAPPING PARAMETER
		1601H RECEIVE PDO 2 MAPPING PARAMETER
		1602H RECEIVE PDO 3 MAPPING PARAMETER
		1603H RECEIVE PDO 4 MAPPING PARAMETER
		1604H RECEIVE PDO 5 MAPPING PARAMETER
		1605H RECEIVE PDO 6 MAPPING PARAMETER
		1606H RECEIVE PDO 7 MAPPING PARAMETER
		1607H RECEIVE PDO 8 MAPPING PARAMETER
		1800H TRANSMIT PDO 1 COMMUNICATION PARAMETER
		1801H TRANSMIT PDO 2 COMMUNICATION PARAMETER
		1802H TRANSMIT PDO 3 COMMUNICATION PARAMETER
		1803H TRANSMIT PDO 4 COMMUNICATION PARAMETER
		1804H TRANSMIT PDO 5 COMMUNICATION PARAMETER
		1805H TRANSMIT PDO 6 COMMUNICATION PARAMETER
		1806H TRANSMIT PDO 7 COMMUNICATION PARAMETER
		1807H TRANSMIT PDO 8 COMMUNICATION PARAMETER
		1A00H TRANSMIT PDO 1 MAPPING PARAMETER
		1A01H TRANSMIT PDO 2 MAPPING PARAMETER
		1A02H TRANSMIT PDO 3 MAPPING PARAMETER
		1A03H TRANSMIT PDO 4 MAPPING PARAMETER
		1A04H TRANSMIT PDO 5 MAPPING PARAMETER
		1A05H TRANSMIT PDO 6 MAPPING PARAMETER
		1A06H TRANSMIT PDO 7 MAPPING PARAMETER
		1A07H TRANSMIT PDO 8 MAPPING PARAMETER
		1F50H PROGRAM DATA
		1F51H PROGRAM CONTROL
		1F57H PROGRAM STATUS
		1F80H NMT STARTUP
		2005H CANOPEN BAUDRATE
		2006H CANOPEN WHEELCONFIG
		2007H CANOPEN CONFIG
		2009H CANOPEN NODEID
		2030H POLE PAIR COUNT
		2031H MAX MOTOR CURRENT
		2034H UPPER VOLTAGE WARNING LEVEL
		2035H LOWER VOLTAGE WARNING LEVEL
		2036H OPEN LOOP CURRENT REDUCTION IDLE TIME
		2037H OPEN LOOP CURRENT REDUCTION VALUE/FACTOR
		2038H BRAKE CONTROLLER TIMING
		2039H MOTOR CURRENTS
		203AH HOMING ON BLOCK CONFIGURATION
		203BH I2T PARAMETERS
		203DH TORQUE WINDOW
		203EH TORQUE WINDOW TIME OUT
		203FH MAX SLIPPAGE TIME OUT
		2057H CLOCK DIRECTION MULTIPLIER
		2058H CLOCK DIRECTION DIVIDER
		205AH ABSOLUTE SENSOR BOOT VALUE (IN USER UNITS)
		205BH CLOCK DIRECTION OR CLOCKWISE/COUNTER CLOCKWISE MODE
		2084H BOOTUP DELAY
		2101H FIELDBUS MODULE AVAILABILITY
		2102H FIELDBUS MODULE CONTROL
		2103H FIELDBUS MODULE STATUS
		2290H PDI CONTROL
		2291H PDI INPUT
		2292H PDI OUTPUT
		2300H NANOJ CONTROL
		2301H NANOJ STATUS
		2302H NANOJ ERROR CODE
		230EH TIMER
		230FH UPTIME SECONDS
		2310H NANOJ INPUT DATA SELECTION
		2320H NANOJ OUTPUT DATA SELECTION
		2330H NANOJ IN/OUTPUT DATA SELECTION
		2400H NANOJ INPUTS
		2410H NANOJ INIT PARAMETERS
		2500H NANOJ OUTPUTS
		2600H NANOJ DEBUG OUTPUT
		2700H USER STORAGE AREA
		2701H CUSTOMER STORAGE AREA
		2800H BOOTLOADER AND REBOOT SETTINGS
		3202H MOTOR DRIVE SUBMODE SELECT
		3203H FEEDBACK SELECTION
		3204H FEEDBACK MAPPING
		320DH TORQUE OF INERTIA FACTOR
		3210H MOTOR DRIVE PARAMETER SET
		3212H MOTOR DRIVE FLAGS
		321AH CURRENT CONTROLLER PARAMETERS
		321BH VELOCITY CONTROLLER PARAMETERS
		321CH POSITION CONTROLLER PARAMETERS
		321DH PRE-CONTROL
		321EH VOLTAGE LIMIT
		3220H ANALOG INPUT DIGITS
		3221H ANALOG INPUTS CONTROL
		3225H ANALOG INPUT SWITCHES
		3240H DIGITAL INPUTS CONTROL
		3241H DIGITAL INPUT CAPTURE
		3242H DIGITAL INPUT ROUTING
		3243H DIGITAL INPUT HOMING CAPTURE
		3250H DIGITAL OUTPUTS CONTROL
		3252H DIGITAL OUTPUT ROUTING
		3320H ANALOG INPUT VALUES
		3321H ANALOG INPUT OFFSETS
		3322H ANALOG INPUT NUMERATORS
		3323H ANALOG INPUT DENOMINATORS
		3380H FEEDBACK SENSORLESS
		33A0H FEEDBACK INCREMENTAL A/B/I 1
		3700H DEVIATION ERROR OPTION CODE
		3701H LIMIT SWITCH ERROR OPTION CODE
		4012H HW INFORMATION
		4013H HW CONFIGURATION
		4014H OPERATING CONDITIONS
		4015H SPECIAL DRIVE MODES
		4016H FACTORY SETTINGS
		4021H BALLAST CONFIGURATION
		4040H DRIVE SERIAL NUMBER
		4041H DEVICE ID
		4042H BOOTLOADER INFOS
		6007H ABORT CONNECTION OPTION CODE
		603FH ERROR CODE
		6040H CONTROLWORD
		6041H STATUSWORD
		6042H VL TARGET VELOCITY
		6043H VL VELOCITY DEMAND
		6044H VL VELOCITY ACTUAL VALUE
		6046H VL VELOCITY MIN MAX AMOUNT
		6048H VL VELOCITY ACCELERATION
		6049H VL VELOCITY DECELERATION
		604AH VL VELOCITY QUICK STOP
		604CH VL DIMENSION FACTOR
		605AH QUICK STOP OPTION CODE
		605BH SHUTDOWN OPTION CODE
		605CH DISABLE OPTION CODE
		605DH HALT OPTION CODE
		605EH FAULT OPTION CODE
		6060H MODES OF OPERATION
		6061H MODES OF OPERATION DISPLAY
		6062H POSITION DEMAND VALUE
		6063H POSITION ACTUAL INTERNAL VALUE
		6064H POSITION ACTUAL VALUE
		6065H FOLLOWING ERROR WINDOW
		6066H FOLLOWING ERROR TIME OUT
		6067H POSITION WINDOW
		6068H POSITION WINDOW TIME
		606BH VELOCITY DEMAND VALUE
		606CH VELOCITY ACTUAL VALUE
		606DH VELOCITY WINDOW
		606EH VELOCITY WINDOW TIME
		606FH VELOCITY THRESHOLD
		6070H VELOCITY THRESHOLD TIME
		6071H TARGET TORQUE
		6072H MAX TORQUE
		6073H MAX CURRENT
		6074H TORQUE DEMAND
		6075H MOTOR RATED CURRENT
		6077H TORQUE ACTUAL VALUE
		607AH TARGET POSITION
		607BH POSITION RANGE LIMIT
		607CH HOME OFFSET
		607DH SOFTWARE POSITION LIMIT
		607EH POLARITY
		607FH MAX PROFILE VELOCITY
		6080H MAX MOTOR SPEED
		6081H PROFILE VELOCITY
		6082H END VELOCITY
		6083H PROFILE ACCELERATION
		6084H PROFILE DECELERATION
		6085H QUICK STOP DECELERATION
		6086H MOTION PROFILE TYPE
		6087H TORQUE SLOPE
		608FH POSITION ENCODER RESOLUTION
		6090H VELOCITY ENCODER RESOLUTION
		6091H GEAR RATIO
		6092H FEED CONSTANT
		6096H VELOCITY FACTOR
		6097H ACCELERATION FACTOR
		6098H HOMING METHOD
		6099H HOMING SPEED
		609AH HOMING ACCELERATION
		60A2H JERK FACTOR
		60A4H PROFILE JERK
		60A8H SI UNIT POSITION
		60A9H SI UNIT VELOCITY
		60B0H POSITION OFFSET
		60B1H VELOCITY OFFSET
		60B2H TORQUE OFFSET
		60C1H INTERPOLATION DATA RECORD
		60C2H INTERPOLATION TIME PERIOD
		60C4H INTERPOLATION DATA CONFIGURATION
		60C5H MAX ACCELERATION
		60C6H MAX DECELERATION
		60E4H ADDITIONAL POSITION ACTUAL VALUE
		60E5H ADDITIONAL VELOCITY ACTUAL VALUE
		60E6H ADDITIONAL POSITION ENCODER RESOLUTION - ENCODER INCREMENTS
		60E8H ADDITIONAL GEAR RATIO - MOTOR SHAFT REVOLUTIONS
		60E9H ADDITIONAL FEED CONSTANT - FEED
		60EBH ADDITIONAL POSITION ENCODER RESOLUTION - MOTOR REVOLUTIONS
		60EDH ADDITIONAL GEAR RATIO - DRIVING SHAFT REVOLUTIONS
		60EEH ADDITIONAL FEED CONSTANT - DRIVING SHAFT REVOLUTIONS
		60F2H POSITIONING OPTION CODE
		60F4H FOLLOWING ERROR ACTUAL VALUE
		60F8H MAX SLIPPAGE
		60FAH CONTROL EFFORT
		60FCH POSITION DEMAND INTERNAL VALUE
		60FDH DIGITAL INPUTS
		60FEH DIGITAL OUTPUTS
		60FFH TARGET VELOCITY
		6502H SUPPORTED DRIVE MODES
		6503H DRIVE CATALOGUE NUMBER
		6505H HTTP DRIVE CATALOGUE ADDRESS

	



	Statusword (6041h) 
	xxxx xxxx x0xx 0000 Not ready to switch on
	xxxx xxxx x1xx 0000 Switch on disabled
	xxxx xxxx x01x 0001 Ready to switch on
	xxxx xxxx x01x 0011 Switched on
	xxxx xxxx x01x 0111 Operation enabled
	xxxx xxxx x00x 0111 Quick stop active
	xxxx xxxx x0xx 1111 Fault reaction active
	xxxx xxxx x0xx 1000 Fault
	
	ModesOfOperation(6060h)
		-2	Auto setup
		-1	Clock-direction mode
		0	No mode change/no mode assigned
		1	Profile Position Mode
		2	Velocity Mode
		3	Profile Velocity Mode
		4	Profile Torque Mode
		5	Reserved
		6	Homing Mode
		7	Interpolated Position Mode
		8	Cyclic Synchronous Position Mode
		9	Cyclic Synchronous Velocity Mode
		10	Cyclic Synchronous Torque Mode

	Controlword (6040h)
	15	14	13	12	11	10	9	8	7	6	5	4	3	2	1	0
	X	X	X	X	X	X	OMS	HLT	FR	OMS[3]		EO	QS	EV	SO
	
		SO (Switched On) : Value = "1": Switches to the "Switched on" state
		EV (Enable Voltage) :Value = "1": Switches to the "Enable voltage" state
		QS (Quick Stop) : Value = "0": Switches to the "Quick stop" state
		EO (Enable Operation) : Value = "1": Switches to the "Enable operation" state
		OMS (Operation Mode Specific) : Meaning is dependent on the selected operating mode
		FR (Fault Reset) : Resets an error or a warning (if possible)
		HALT : Value = "1": Triggers a halt; valid in the following modes:
		Profile Position
		Velocity
		Profile Velocity
		Profile Torque
		Interpolated Position Mode

		void yield() 
		This function returns the processor time to the operating system. 
		In the next time slot, the program continues at the location after the call.

		Void sleep (U32 ms)
		This function returns the processor time to the operating system for the specified number of milliseconds.
		The user program is then continued at the location after the call.

*/

void user(){
		
	BootDelay = 100;
	MotorDirection =0;
	InOut.TargetVelocity = 0;				//start with 0 speed.
	ModesOfOperation(3); 					//what is mode?
	
	

}

/*
* Steps for Controller;
Start Delay
halt Motor
reset all buffers
reset all do/di 

set default values
	-motor direction
	-motor under closed loop
	-motor lowest speed
	-motor boot position
	
	
if connection/data not recived
halt motor naturally
always poke the master


*/