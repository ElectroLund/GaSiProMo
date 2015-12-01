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
#define LEDFADER				13

#define MAX_ADDR_PINS		5
#define MAX_DATA_PINS		8

#define EXTRA_DEBUG			false

//-------------
// globals
//-------------
												// D0  ......						D7
const byte DATA_PINS[MAX_DATA_PINS] = { 22, 23, 24, 25, 26, 27, 28, 29 };
												//  A0  .....		 A4
const byte ADDR_PINS[MAX_ADDR_PINS] = { 47, 48, 49, 50, 51 };
const byte FL =	52;
const byte RST =	53;

// incoming serial byte
byte inByte = 0;

// address counter (must only use A0-A2)
#define BASE_ADDRESS		0b11111000
byte address;
#define CHAR_DELAY		50

String inputString = "";			// a string to hold incoming data
char inChar = 0;
boolean stringComplete = false;  // whether the string is complete

int buttonState = 0;			// variable for reading the pushbutton status
const int buttonPin = 35;	  // the number of the pushbutton pin
int bootupOption = false;	  // variable for running mode


// the setup function runs once when you press reset or power the board
void setup()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);

	// reserve 200 bytes for the inputString:
	inputString.reserve(200);

	// wait for serial port to connect. Needed for native USB port only
	while (!Serial);

	// button
	pinMode(buttonPin, INPUT);
	
	// prints title with ending line break
	Serial.println(">>>>>>>> OsRAM intelligent LED display <<<<<<<<");

	// setup the display buses
	BusConfig();

	// clear all characters
	ResetDisplay();

	// disable flashing
	digitalWrite(FL, HIGH);

	// bootup options
	if (bootupOption = digitalRead(buttonPin))
	{
		Serial.println("\nboot mode #2, console mode");
		
		// trap for closed switch
		Serial.println("please release switch now!");
		while (!digitalRead(buttonPin));
	}
	else
	{
		Serial.println("\nboot mode #1, normal mode");
	}
}

// the loop function runs over and over again forever
void loop()
{	
	if (bootupOption == true)
	{	
		StringWrite(" Z X Y W");
	
		delay(1200);
		//ResetDisplay();
	
		StringWrite("abcdefgh");
	
		delay(1200);
		//ResetDisplay();
	
		StringWrite("12345678");
	
		delay(1200);
		//ResetDisplay();
	}
	
	else
	{
		// look for consol input
		while (Serial.available())
		{
			// get the new byte:
			inChar = (char)Serial.read();
						
			// if the incoming character is a newline, set a flag
			// so the main loop can do something about it:
			if (inChar == '\n')
			{
				stringComplete = true;
			}
			// don't add newlines
			else
			{
				// add characters to string
				inputString += inChar;
			}
		}

		// now print the string when ready
		if (stringComplete)
		{
			// send to display
			StringWrite(inputString);
			
			// echo
			Serial.println(inputString);
			
			// clear the string:
			inputString = "";
			stringComplete = false;
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

/*------------------------
string write function
input is an ASCII string that
must be written 1 character at a time
------------------------*/
void StringWrite(String message)
{
	byte address = BASE_ADDRESS;

	// first clear all characters
	ResetDisplay();

	#if EXTRA_DEBUG
	Serial.println("\nstring length = ");
	Serial.print(message.length());
	#endif

	for (int i = 0; i < message.length(); i++, address++)
	{
		#if EXTRA_DEBUG
		Serial.println("\ncharacter = ");
		Serial.print(message.charAt(i));
		#endif

		// set up the display character
		AddressBusWrite(address);

		// setup delay?
		delay(CHAR_DELAY);
				
		// write the string character to that display character
		DataBusWrite(message.charAt(i));
		delay(CHAR_DELAY);
	}	
}


/*------------------------
display reset function 
clears all characters and blink
formats
------------------------*/
void ResetDisplay(void)
{
	digitalWrite(RST, LOW);
	delay(CHAR_DELAY);
	
	digitalWrite(RST, HIGH);
	delay(CHAR_DELAY);
}