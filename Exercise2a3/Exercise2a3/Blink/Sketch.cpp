


/*

Author : Mechenane khalef
Date   :19/09/2019

Blinking leds of 7-segment display 

*/


#include <Arduino.h>

#define aPin 2
#define bPin 8
#define cPin 6
#define dPin 5
#define fPin 3
#define ePin 4
#define gPin 7

//blink number 3 and letter E three times 

void sequenceSegments() {
	
	for (int i = 0 ; i < 3 ; i++) {
		
	digitalWrite(fPin,HIGH);
	digitalWrite(ePin,HIGH);
	delay(1000);
	digitalWrite(fPin,LOW);
	digitalWrite(ePin,LOW);
	digitalWrite(bPin,HIGH);
	digitalWrite(cPin,HIGH);
	delay(1000);
	digitalWrite(bPin,LOW);
	digitalWrite(cPin,LOW);
	
	}
}

//turn leds off smoothly

void turnLightOff(){
// loop to turn leds Off
 for( int i = 2 ; i < 9 ; i++)
  {
    digitalWrite(i,HIGH);
    delay(600);
  }

}

//turn off all the leds 

void lightOff(){
	
	digitalWrite(aPin,HIGH);
	digitalWrite(bPin,HIGH);
	digitalWrite(cPin,HIGH);
	digitalWrite(dPin,HIGH);
	digitalWrite(ePin,HIGH);
	digitalWrite(fPin,HIGH);
	digitalWrite(gPin,HIGH);
	
}

// Turn on all the leds

void lightOn(){
	
	digitalWrite(aPin,LOW);
	digitalWrite(bPin,LOW);
	digitalWrite(cPin,LOW);
	digitalWrite(dPin,LOW);
	digitalWrite(ePin,LOW);
	digitalWrite(fPin,LOW);
	digitalWrite(gPin,LOW);
	
}

//make a circle counter clockwise three times (leds light up smoothly)

void counterClockWise(){
	
  // loop to turn leds ON 
  for (int j = 0 ;j < 3 ;j++) {
     
       digitalWrite(aPin,LOW);
       delay(600);
	   digitalWrite(fPin,LOW);
	   delay(600);
	   digitalWrite(ePin,LOW);
	   delay(600);
	   digitalWrite(dPin,LOW);
	  delay(600);
      digitalWrite(cPin,LOW);
	  delay(600);
	  digitalWrite(bPin,LOW);
	  delay(600);
  
     lightOff();
  }
}

//make a circle clockwise three times
void lightClockWise() {
	// loop to turn leds ON  3 times 
	   for(int j = 0 ; j < 3 ; j++)
	   {
		  digitalWrite(aPin,LOW);
		  delay(600);
		  digitalWrite(bPin,LOW);
		  delay(600);
		  digitalWrite(cPin,LOW);
		  delay(600);
		  digitalWrite(dPin,LOW);
		  delay(600);
		  digitalWrite(ePin,LOW);
		  delay(600);
		  digitalWrite(fPin,LOW);
		  delay(600);
		  
		   lightOff();
	   }
  }
 
 
// the setup function runs once when you press reset or power the board

void setup() {
	
  // initialize digital pin (2,3,4,5,6,7,8) as an output.
  
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(gPin, OUTPUT);

}

// the loop function runs over and over again forever

void loop() {
	
	sequenceSegments();////blink number 3 and letter E three times
	lightOff();//turn all LEDs off
	delay(1000);
    counterClockWise();//make a circle counter clockwise three times (leds light up smoothly)
	lightOn();//turn all LEDs on
	delay(1000);
	turnLightOff();
	lightOn();//turn all LEDs on
	delay(1000);
	turnLightOff();
	lightOn();//turn all LEDs on
	delay(1000);
	turnLightOff();
	delay(1000);
	lightClockWise();//make a circle clockwise three times
	lightOn();//turn all LEDs on
	
}
