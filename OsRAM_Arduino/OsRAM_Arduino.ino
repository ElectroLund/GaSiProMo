 /*************************************
  OsRAM
  Controls the IPD2131 intelligent display

  Heartbeat LED on pin 13.
  
  Arduino documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified November 3, 2015
  by Rob Lund
 ***************************************/

/***********
defines 
************/
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

#define MAX_ADDRES_PINS         5
#define MAX_DATA_PINS           8
                                     // D0  ......                  D7
const byte DATA_PINS[MAX_DATA_PINS] = { 22, 23, 24, 25, 26, 27, 28, 29 };
                                    //  A0  .....       A4
const byte ADDR_PINS[MAX_ADDR_PINS] = { 47, 48, 49, 50, 51 };


const byte DISPLAY_STRING[6] = { 1, 1, 1, 0, 1, 0 };

// the setup function runs once when you press reset or power the board
void setup()
{
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
  BusConfig();
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(LEDFADER, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LEDFADER, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}


// --------------------------
// bus port config
// --------------------------
void BusConfig(void)
{
    int i;
    
    for (i=0; i<MAX_ADDR_PINS; i++)
    {
        pinMode(ADDR_PINS[i], OUTPUT);
    }

    for (i=0; i<MAX_DATA_PINS; i++)
    {
        pinMode(DATA_PINS[i], OUTPUT);
    }
}

// ------------------------
// data bus write function
// ------------------------
void DataBusWrite(byte data[])
{
    for (int i=0; i<MAX_DATA_PINS; i++)
    {
        digitalWrite(DATA_PINS[i], data[i]);
    }
}


// --------------------------
// address bus write function
// --------------------------
void AddressBusWrite(byte address[])
{
    for (int i=0; i<MAX_ADDR_PINS; i++)
    {
        digitalWrite(ADDR_PINS[i], address[i]);
    }   
}
