/*****************************************************************************/
//Team:    Gustavo Correa, Jiunn Siow,Augustin Balquin
//Project: 3D LED MATRIX CUBE
//Date:    April 22-24, 2016
//Event:   SB Hacks II, UC Santa Barbara
//Challenge: IBM Watson IoT Challenge
//Status: Won challenge
//Description: This code serves to output a single LED and serves as a template for 
//             future projects
 
/*The overall concept was to create a physical IBM Watson (similar to Jarvis from Iron Man)
 * that would serve as a physical App Hub with a variety of interactive applications. 
 * Some application ideas were a weather app that would display a bit image representing 
 * whether it was sunny or rainy outside, or a music visualizer which would represent the different
 * frequencies of a song.
  
 * This Project was created with Node-Red on the bluemix platform. 
 * The code on the bluemix platform contains only the simulated weather data that was run on the raspberry pi. 
 * The program filtering the data is present on bluemix and connects to an arduino 
 * with python scripts edited by Agustin Balquin and Gustavo Correa.  
 * Jiunn Siow configured the leap motion technology that allows us to "swipe" 
 left and right to navigate through the LED Matrix interface.*/
/*******************************************************************************/
//anode pins of shift register
int clockPin = 7;
int latchPin = 6;
int dataPin = 5;

//cathode pins of shift register
int clockPinx = 4;
int latchPinx = 3;
int dataPinx = 2;

//left most bit is x=0,y=0 of the coordinate plane
byte ledStates[8] =  {B10000000};
byte GroundLEDs[8] = {B00111111};

//function prototypes
void GroundCorrectLED (byte states);
void SetStates (byte statesx);
byte xPosition(int dig);
byte yPosition(int dig);


void setup() {
  pinMode(latchPinx, OUTPUT);
  pinMode(clockPinx, OUTPUT);
  pinMode(dataPinx, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);

  Serial.begin(9600);
}


void loop() {

  setLed(B01111111, B10000000);
}

// Parameters are byte data types that represent the binary input for specific LEDS
void setLed(byte anode_x, byte cathode_y)
{
  SetStates(cathode_y);
  GroundCorrectLED (anode_x);

  return;
}

//sets the ground pins of the matrix
void GroundCorrectLED (byte states) {

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, states);
  digitalWrite(latchPin, HIGH);

}

//sets the cathode pins of the matrix
void SetStates (byte statesx) {

  digitalWrite(latchPinx, LOW);
  shiftOut(dataPinx, clockPinx, LSBFIRST, statesx);
  digitalWrite(latchPinx, HIGH);

}

//parameter is an integer that represents the decimal val for x coordinate position
// return value is byte data type that represents decimal value
byte xPosition(int dig)
{
  if (dig == 0)
    return B01111111;
  if (dig == 1)
    return B10111111;
  if (dig == 2)
    return B11011111;
  if (dig == 3)
    return B11101111;

  if (dig == 4)
    return B11110111;
  if (dig == 5)
    return B11111011;
  if (dig == 6)
    return B11111101;
  if (dig == 7)
    return B11111110;
}

//parameter is an integer that represents the decimal value for y coordinate position
// return value is byte data type that represents decimal value
byte yPosition(int dig)
{
  if (dig == 0)
    return B10000000;
  if (dig == 1)
    return B01000000;
  if (dig == 2)
    return B00100000;
  if (dig == 3)
    return B00010000;

  if (dig == 4)
    return B00001000;
  if (dig == 5)
    return B00000100;
  if (dig == 6)
    return B00000010;
  if (dig == 7)
    return B00000001;
}


//resets the entire matrix,
//sets all cathodes to low and anodes to high
void resetLeds()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);

  digitalWrite(latchPinx, LOW);
  shiftOut(dataPin, clockPinx, LSBFIRST, B00000000);
  digitalWrite(latchPinx, HIGH);

  return;
}

