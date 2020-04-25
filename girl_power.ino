#include <Wire.h>
#include "paj7620.h"
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

#define GES_REACTION_TIME    150       // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME      800       // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME     500

JQ6500_Serial mp3(8,9);

uint8_t error = 0;

void Gesture(){
  uint8_t data = 0, data1 = 0;
  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
          mp3.playFileByIndexNumber(2);
        }          
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
          mp3.playFileByIndexNumber(3);
        }          
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Up");
        }          
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Down");
        }          
        break;
      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        Serial.println("Backward");
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
        }
        break;
    }
  }
  delay(100);
  
}



void setup() {
  
  Serial.begin(115200);
  mp3.begin(9600);
  mp3.reset();
  //statusAndHelpOutput();

  mp3.setVolume(30);
  mp3.setEqualizer(MP3_EQ_NORMAL);
  mp3.playFileByIndexNumber(1);

  error = paj7620Init();      // initialize Paj7620 registers
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:"); Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }


}

void loop() {
  Gesture();

}
