
/*
Author : Mechenane khalef
Date   :19/09/2019
Blinking leds with Code traffic (red -> red & yellow -> green -> yellow -> red),

*/

#include <Arduino.h>

//intruppt pin


#define INTERRUPTPIN 2

volatile boolean state = false ;

volatile int countClickNumber = 0 ;

volatile int readPinSource = 0;      // variable to store the read value



void trafficLights(int);
void buttonClicked();


// the setup function runs once when you press reset or power the board

void setup() {
	
	// initialize digital pins (4,5,6,7) as an output.
	
	DDRD |= ((1<<2)|(1<<4)|(1<<5)|(1<<6)|(1<<7));

	attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN),buttonClicked,CHANGE);

}

// the loop function runs over and over again forever

void loop() {
	
	if (state){	
		trafficLights(countClickNumber);
	}
}

void trafficLights(int parameter){
	
	switch (parameter){
		
		//Blink the Red Led
		case(1):
		PORTD |= (1<<4);   // turn the LED on (HIGH is the voltage level)
		delay(500);       // wait for a second
		PORTD &= ~(1<<4) ;  // turn the LED off by making the voltage LOW
		delay(500);
		break;
		
		case(2):
		//blink red and yellow
		PORTD |= (1<<4);
		PORTD |= (1<<6);
		delay(500);
		PORTD &= ~(1<<4) ;
		PORTD &= ~(1<<6) ;
		delay(500);
		break;
		
		//blink the green
		case(3):
		PORTD |= (1<<5);
		delay(500);
		PORTD &= ~(1<<5);
		delay(500);
		break;
		
		case(4):
		//blink the yellow led
		PORTD |= (1<<6);
		delay(500);
		PORTD &= ~(1<<6) ;
		delay(500);
		break;
		
		//Blink the Red Led
		case(5):
		PORTD |= (1<<4);   // turn the LED on (HIGH is the voltage level)
		delay(500);       // wait for a second
		PORTD &= ~(1<<4) ;  // turn the LED off by making the voltage LOW
		delay(500);
		break;
	}
}

void buttonClicked(){
	
	
	//read the state of the interrupt pin 
	readPinSource = digitalRead(INTERRUPTPIN);

	if (readPinSource == 0 ){
		
		state = true;
		
		countClickNumber += 1 ;
		
		if( countClickNumber == 6){
			
			countClickNumber = 0;	
		}
	}
}