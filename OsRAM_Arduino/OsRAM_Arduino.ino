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

#define MAX_ADDR_PINS         5
#define MAX_DATA_PINS         8

//-------------
// globals
//-------------
												// D0  ......                  D7
const byte DATA_PINS[MAX_DATA_PINS] = { 22, 23, 24, 25, 26, 27, 28, 29 };
												//  A0  .....       A4
const byte ADDR_PINS[MAX_ADDR_PINS] = { 47, 48, 49, 50, 51 };
const byte FL =	52;
const byte RST =	53;

// incoming serial byte
byte inByte = 0;

// address counter (must only use A0-A2)
#define BASE_ADDRESS		0b11111000
byte address;
#define CHAR_DELAY		500

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

	// setup the display buses
	BusConfig();

	// reset display
	digitalWrite(RST, LOW);
	delay(10);
	digitalWrite(RST, HIGH);

	// disable flashing
	digitalWrite(FL, HIGH);
}

// the loop function runs over and over again forever
void loop()
{

	StringWrite("Hello!");

	delay(1500);

	StringWrite("        ");

	delay(1500);
	
	StringWrite("TITS");

	StringWrite("        ");

	delay(1500);
	
	StringWrite("U-S2k");

	delay(1500);
	
	StringWrite("        ");

	delay(1500);
/*
	
	// start with 1st digit:
	AddressBusWrite(address = BASE_ADDRESS);

	// now some junk an ASCII message
	DataBusWrite('H');
	delay(CHAR_DELAY);

	AddressBusWrite(++address);

	// now some junk an ASCII message
	DataBusWrite('e');
	delay(CHAR_DELAY);

	AddressBusWrite(++address);
	
	// now some junk an ASCII message
	DataBusWrite('l');
	delay(CHAR_DELAY);

	AddressBusWrite(++address);
	
	// now some junk an ASCII message
	DataBusWrite('l');
	delay(CHAR_DELAY);
	
	AddressBusWrite(++address);
	
	// now some junk an ASCII message
	DataBusWrite('o');
	delay(CHAR_DELAY);
	
	AddressBusWrite(++address);
	
	// now some junk an ASCII message
	DataBusWrite('!');
	delay(CHAR_DELAY);

*/
	
	#if 0
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

#endif
	
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

	pinMode(FL, OUTPUT);
	pinMode(RST, OUTPUT);
}

/* ------------------------
data bus write function
input is a hex byte that 
must be written 1 bit at at time
------------------------*/
void DataBusWrite(byte data)
{	
	for (int i = 0; i < MAX_DATA_PINS; i++)
	{
		// write the bus		
		digitalWrite(DATA_PINS[i], bitRead(data, i));
	}
}


/* ------------------------
address bus write function
input is a hex byte that 
must be written 1 bit at at time
------------------------*/
void AddressBusWrite(byte address)
{
	for (int i = 0; i < MAX_ADDR_PINS; i++)
	{
		// write the bus	
		digitalWrite(ADDR_PINS[i], bitRead(address, i));
	}
}

/* ------------------------
string write function
input is an ASCII string that
must be written 1 character at a time
------------------------*/
void StringWrite(String message)
{
	byte address = BASE_ADDRESS;
	
	Serial.println("\nstring length = ");
	Serial.print(message.length());

	for (int i = 0; i < message.length(); i++, address++)
	{
		Serial.println("\ncharacter = ");
		Serial.print(message.charAt(i));

		// set up the display character
		AddressBusWrite(address);

		// write the string character to that display character
		DataBusWrite(message.charAt(i));
		delay(CHAR_DELAY);
	}	
}

