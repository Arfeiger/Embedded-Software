/*

Author : Mechenane khalef 
Date   :19/09/2019
Blinking leds with Code traffic (red -> red & yellow -> green -> yellow -> red),

*/


#include <Arduino.h>

#define redPin 13
#define yellowPin 12
#define greenPin 11


// the setup function runs once when you press reset or power the board

void setup() {
	
  // initialize digital pins (11,12,13) as an output.
  
  pinMode(redPin, OUTPUT);  // Green Led
  pinMode(yellowPin, OUTPUT);  // Yellow Led
  pinMode(greenPin, OUTPUT);  // Red Led 
  
}

// the loop function runs over and over again forever

void loop() {
	
  //Blink the Red Led 
  
  digitalWrite(redPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(redPin, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);              // wait for a second
  
  //Blink the red & yellow leds 
  
  digitalWrite(yellowPin, HIGH);   
  digitalWrite(redPin, HIGH);
  delay(1000);  
  digitalWrite(yellowPin, LOW);   
  digitalWrite(redPin, LOW);
      
          
  //Blink the green led
  
  digitalWrite(greenPin, HIGH);   
  delay(1000);              
  digitalWrite(greenPin, LOW);    
  
  //blink the yellow led 
  
  digitalWrite(yellowPin, HIGH);   
  delay(1000);              
  digitalWrite(yellowPin, LOW);    

}
