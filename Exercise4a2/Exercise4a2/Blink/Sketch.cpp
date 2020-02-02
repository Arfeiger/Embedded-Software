/*
 * author  : Mechenane Khalef 
 * Date    : 29/10/2019
 * version : 1.0
 * Description : This program implements 4 LEDs (2 red LEDs, one green and one yellow) where the change of state of the green and yellow triggers an interrupt
 *
 */

//interrupts pins 

#include <Arduino.h>

const byte interruptFirstPin = 2;
const byte interruptSecondPin = 3;

volatile boolean interruptStateGreen = false;
volatile boolean interruptStateYellow = false;



void blinkFirstRedLEd();
void blinkSecondRedLed();

void setup() {
  
  //sitting up pins (6,7) as outputs
  
  DDRD |=((1<<2)|(1<<3)|(1<<6)|(1<<7));
  
  attachInterrupt(digitalPinToInterrupt(interruptFirstPin),blinkFirstRedLEd,CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptSecondPin),blinkSecondRedLed,CHANGE);
}

//ISR that control the first red led 

void blinkFirstRedLEd()
{
  if( interruptStateGreen ){ //if the event is triggered
     PORTD |= (1<<6);//turn on the first red led
  }
  else {
    PORTD &= ~(1<<6);//turn off the first red led 
  }
}
//ISR that control the second red led 
void blinkSecondRedLed()
{
  if( interruptStateYellow ){
      PORTD &= ~(1<<7); //turn on the second red led 
  }
  else {
     PORTD |= (1<<7);//turn off the second red led 
  }
}

void loop() {

   PORTD |= (1<<2); //turn on green led  
   PORTD |= (1<<3); //turn on yellow led 
   delay(500);     
   interruptStateYellow = true ; 
   PORTD &= ~(1 <<3); //turn off the yellow led    
   delay(500); 
   interruptStateYellow = false ; 
   interruptStateGreen = true ;         
   PORTD &= ~(1 <<2); //turn off green led    
   PORTD |= (1<<3); //turn on yellow led 
   delay(500);   
   interruptStateYellow = true ;  
   PORTD &= ~(1 <<3); //turn off the yellow led    
   delay(500);
   interruptStateYellow = false ;
   interruptStateGreen = false ;
  
 
}