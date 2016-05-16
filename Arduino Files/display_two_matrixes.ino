/*****************************************************************************/
//Team:    Gustavo Correa, Jiunn Siow,Agustin Balquin
//Project: 3D LED MATRIX CUBE
//Date:    April 22-24, 2016
//Event:   SB Hacks II, UC Santa Barbara
//Challenge: IBM Watson IoT Challenge
//Status: Won challenge
//Description: This code serves output on two matrixes. Currently both matrixes are
//            connected to the same anode shift register, but individual cathode
//            shift registers.
 
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
int clockPin = 7;
int latchPin = 6;
int dataPin = 5;

int clockPinx = 4;
int latchPinx = 3;
int dataPinx = 2;


byte matrix1[8] =  {B10000000};
byte matrix2[8] =  {B10000000};
byte Ground[8] = {B01111111};

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
  
    digitalWrite(latchPinx, LOW);
    shiftOut(dataPinx, clockPinx, LSBFIRST, matrix1[0]);  
    shiftOut(dataPinx, clockPinx, LSBFIRST, matrix2[0]); 
    digitalWrite(latchPinx, HIGH);
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, Ground[0]);
    digitalWrite(latchPin, HIGH);


    for(int r = 0; r < 8; ++r)
    {
      for( int c = 0; c < 8; ++c)
      {
        doubleMatrixLight(r,c,c,r);
        delay(10);
      }
    }
    
}

void doubleMatrixLight(int r0, int c0, int r1, int c1)
{
  byte matrix1_xpos = xPosition(c0);
  byte matrix1_ypos = yPosition(r0);
  byte matrix2_xpos = xPosition(c1);
  byte matrix2_ypos = yPosition(r1);

  GroundCorrectLED(matrix1_xpos);
  digitalWrite(latchPinx, LOW);
  shiftOut(dataPinx, clockPinx, LSBFIRST, matrix1_ypos);  
  shiftOut(dataPinx, clockPinx, LSBFIRST, matrix2_ypos); 
  digitalWrite(latchPinx, HIGH);
  
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

