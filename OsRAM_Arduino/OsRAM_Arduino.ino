/*************************************
OsRAM
Controls the IPD2131 intelligent display

Heartbeat LED on pin 13.

Arduino documentation at http://www.arduino.cc

This example code is in the public domain.

modified November 3, 2015
by Rob Lund
***************************************/

//-------------
// definitions
//-------------
#define LEDFADER      13

/*
#define OSRAM_RESET   53
#define OSRAM_FL      52
#define OSRAM_A4      51
#define OSRAM_A3      50
#define OSRAM_A2      49
#define OSRAM_A1      48
#define OSRAM_A0      47
*/

#define MAX_ADDR_PINS         5
#define MAX_DATA_PINS         8


//-------------
// globals
//-------------
												// D0  ......                  D7
const byte DATA_PINS[MAX_DATA_PINS] = { 22, 23, 24, 25, 26, 27, 28, 29 };
												//  A0  .....       A4
const byte ADDR_PINS[MAX_ADDR_PINS] = { 47, 48, 49, 50, 51 };

// incoming serial byte
byte inByte = 0;

// the setup function runs once when you press reset or power the board
void setup()
{

	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	// prints title with ending line break
	Serial.println(">>>>>>>> OsRAM intelligent LED display <<<<<<<<");

	// heartbeat setup
	pinMode(LEDFADER, OUTPUT);
	/*
	pinMode(OSRAM_RESET, OUTPUT);
	pinMode(OSRAM_FL, OUTPUT);
	pinMode(OSRAM_A4, OUTPUT);
	pinMode(OSRAM_A3, OUTPUT);
	pinMode(OSRAM_A2, OUTPUT);
	pinMode(OSRAM_A1, OUTPUT);
	pinMode(OSRAM_A0, OUTPUT);
	*/
	// setup the display buses
	BusConfig();
}

// the loop function runs over and over again forever
void loop()
{
	// heartbeat
	digitalWrite(LEDFADER, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);              // wait for a second
	digitalWrite(LEDFADER, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);              // wait for a second


  // if we get a valid byte, format it (TEST)
	if (Serial.available() > 0)
	{
		// get incoming byte:
		inByte = Serial.read();

		// verify it's ASCII
		if (isPrintable(inByte))
		{
			DataBusWrite(inByte);
		}
	}
}


// --------------------------
// bus port config
// --------------------------
void BusConfig(void)
{
	int i;
	
	for (i = 0; i < MAX_ADDR_PINS; i++)
	{
		pinMode(ADDR_PINS[i], OUTPUT);
	}
	
	for (i = 0; i < MAX_DATA_PINS; i++)
	{
		pinMode(DATA_PINS[i], OUTPUT);
	}
}

/* ------------------------
data bus write function
data is a hex byte
------------------------*/
void DataBusWrite(byte data)
{
	byte bit = 0;
	
	for (int i = 0; i < MAX_DATA_PINS; i++)
	{
		// split the data byte into bits
		bit = data & (1 << i);

		// echo
		Serial.print("bit: ");
		Serial.print(i, DEC);
		Serial.write(bit);
		Serial.println();

		// write the bus		
		digitalWrite(DATA_PINS[i], bit);
	}
}


/* ------------------------
address bus write function
data is a hex byte
------------------------*/
void AddressBusWrite(byte address)
{
	byte bit = 0;
	
	for (int i = 0; i < MAX_ADDR_PINS; i++)
	{
		// split the data byte into bits
		bit = address & (1 << i);

		// echo
		Serial.print("bit: ");
		Serial.print(i, DEC);
		Serial.write(bit);
		Serial.println();

		// write the bus	
		digitalWrite(ADDR_PINS[i], bit);
	}
}
