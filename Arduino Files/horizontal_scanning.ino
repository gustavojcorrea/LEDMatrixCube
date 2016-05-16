/*****************************************************************************/
//Team:    Gustavo Correa, Jiunn Siow,Agustin Balquin
//Project: 3D LED MATRIX CUBE
//Date:    April 22-24, 2016
//Event:   SB Hacks II, UC Santa Barbara
//Challenge: IBM Watson IoT Challenge
//Status: Won challenge
//Description: This code serves to scan through all LEDs on LED Matrix to
//             verify that the Matrixes are outputting correctly.
 
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
int clockPinx = 4;
int latchPinx = 3;
int dataPinx = 2;

int clockPin = 7;
int latchPin = 6;
int dataPin = 5;


byte ledStates[8] =  {B10000000};
byte GroundLEDs[8] = {B00111111};

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
 
    Serial.begin(9600);
}


void loop() {
  
  for(int i=0; i<8;i++)
  {
      for(int j = 0; j < 8; ++j)
      {
         byte x =  xPosition(i);
         byte y =  yPosition(j);
    
         setLed(x,y);
         delay(100);
         //resetLeds();
      }
  }

}

void GroundCorrectLED (byte states){
  
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, states);  
    digitalWrite(latchPin, HIGH);
    
}

void SetStates (byte statesx){
       
    digitalWrite(latchPinx, LOW);
    shiftOut(dataPinx, clockPinx, LSBFIRST, statesx);  
    digitalWrite(latchPinx, HIGH);
    
     }
     

byte xPosition(int dig)
{
  if(dig == 0)
     return B01111111;
  if(dig == 1)
     return B10111111;
  if(dig == 2)
     return B11011111;
  if(dig == 3)
     return B11101111;
     
  if(dig == 4)
     return B11110111;
  if(dig == 5)
     return B11111011;
  if(dig == 6)
     return B11111101;
  if(dig == 7)
     return B11111110;    
}

byte yPosition(int dig)
{
  if(dig == 0)
     return B10000000;
  if(dig == 1)
     return B01000000;
  if(dig == 2)
     return B00100000;
  if(dig == 3)
     return B00010000;
     
  if(dig == 4)
     return B00001000;
  if(dig == 5)
     return B00000100;
  if(dig == 6)
     return B00000010;
  if(dig == 7)
     return B00000001;    
}

void setLed(byte anode_x, byte cathode_y)
{
    SetStates(cathode_y);
    GroundCorrectLED (anode_x);

    return;
}

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

