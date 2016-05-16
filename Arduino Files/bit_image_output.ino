/*****************************************************************************/
//Team:    Gustavo Correa, Jiunn Siow,Agustin Balquin
//Project: 3D LED MATRIX CUBE
//Date:    April 22-24, 2016
//Event:   SB Hacks II, UC Santa Barbara
//Challenge: IBM Watson IoT Challenge
//Status: Won challenge
//Description: This code serves to display bit images using binary arrays.
 
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

int clockPin = 4;
int latchPin = 3;
int dataPin = 2;

int clockPinx = 7;
int latchPinx = 6;
int dataPinx = 5;

//binary arrays
byte sun_image[8] =  {B10101010,
                      B00000001,
                      B10111100,
                      B01111101,
                      B10111100,
                      B00111101,
                      B10000000,
                      B01010101};
                      
byte circle_image[8] =  {B10101010,
                      B00000001,
                      B10111100,
                      B01111101,
                      B10111100,
                      B00111101,
                      B10000000,
                      B01010101};
byte GroundLEDs[8] = {B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001};

//function prototypes
void GroundCorrectLED (byte states);
void SetStates (byte statesx);


void setup() {
  pinMode(latchPinx, OUTPUT);
  pinMode(clockPinx, OUTPUT);
  pinMode(dataPinx, OUTPUT);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, LSBFIRST, B11111111);  
//    digitalWrite(latchPin, HIGH);
//    
    Serial.begin(9600);
}

void loop() {
  
  for(int i=0;i<8;i++)
  {
    SetStates(sun_image[i]);
    GroundCorrectLED(GroundLEDs[i]);
    delay(2);
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
     

