#include <Wire.h>
#include "paj7620.h"
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

#define GES_REACTION_TIME    800       // You can adjust the reaction time according to the actual circumstance.
//#define GES_ENTRY_TIME      800       // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
//#define GES_QUIT_TIME     250

#define interruptPin  2

unsigned long previousMillis = 0 ;
unsigned long interval = 800L;       

JQ6500_Serial mp3(8,9);

uint8_t error = 0;
uint8_t data = 0, data1 = 0;

void Gesture(){
    
  error = paj7620ReadReg(0x43, 1, &data);    
//  Serial.println(data);
  if (!error) 
  {
  if      (data==GES_CLOCKWISE_FLAG) { Serial.println("Clockwise");}
  else if (data==GES_COUNT_CLOCKWISE_FLAG) {Serial.println("anti-clockwise");}
  else if (data==GES_RIGHT_FLAG) {
        Serial.println("Right");
        mp3.playFileByIndexNumber(4);
      }
  else if (data==GES_LEFT_FLAG) {
        Serial.println("Left");
        mp3.playFileByIndexNumber(5);
      }
  else if (data==GES_UP_FLAG) { 
        Serial.println("Up");
        mp3.playFileByIndexNumber(2);
      }
  else if (data==GES_DOWN_FLAG) {
        Serial.println("Down");
        mp3.playFileByIndexNumber(3);
      }
  else if (data==GES_FORWARD_FLAG) {
        Serial.println("Forward");
        mp3.playFileByIndexNumber(6);
      }
  else if (data==GES_BACKWARD_FLAG) {
        Serial.println("Backward");
        mp3.playFileByIndexNumber(7);
      }
  delay(GES_REACTION_TIME);
   
 }
  
}



void setup() {
  
  Serial.begin(115200);
  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(30);
  mp3.setEqualizer(MP3_EQ_NORMAL);
  mp3.playFileByIndexNumber(1);
  error = paj7620Init();      // initialize Paj7620 registers
  if (error)   {Serial.print("INIT ERROR,CODE:"); Serial.println(error); }
  else         {Serial.println("INIT OK"); }

  
}


void loop() {
  
  if ( millis() - previousMillis >= interval) { 
        Gesture(); 
        previousMillis = millis();               
  }

}
