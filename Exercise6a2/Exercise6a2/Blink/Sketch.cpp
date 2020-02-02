/*
* Name    : Mechenane Khalef 
* Date    : 05/12/2019
* version : 1.0
* Program Description : to program is to display numbers from 0 to 99 using two 7 segment display and two push buttons

*/
#include <Arduino.h>




//interrupt source to control the blue 7 segment display
#define INTERRUPTPINBLUE 2

//interrupt source to control the red 7 segment display
#define INTERRUPTPINRED 3

volatile boolean stateRed = false ;
//count the click numbers
volatile int countClickNumberRed = 0 ;
//read the state of the interrupt source 
volatile int readPinSourceRed = 0;


volatile boolean stateBlue = false ;
//count the click numbers
volatile int countClickNumberBlue = 0 ;
//read the state of the interrupt source 
volatile int readPinSourceBlue = 0;


//functions 
void buttonClickedRed();
void buttonClickedBlue();
void diplayDigitBlue();
void displayDigitsRed();

// the setup function runs once when you press reset or power the board
void setup() {
	
//set up the 7 segment display with red wires 
DDRD  |= ((1<<4)|(1<<5)|(1<<6)|(1<<7));//pins(4,5,6,7)
DDRB  |= ((1<<0)|(1<<1)|(1<<2));//pins (8,9,10)

//set up the 7 segment display with blue wires 
DDRB  |= ((1<<5));//pins(13)
DDRC  |= ((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));//pins (A0,A1,A2,A3,A4,A5)

//ISR for red 7 Segment display 
attachInterrupt(digitalPinToInterrupt(INTERRUPTPINRED),buttonClickedRed,CHANGE);

//ISR for blue 7 Segment display 
attachInterrupt(digitalPinToInterrupt(INTERRUPTPINBLUE),buttonClickedBlue,CHANGE);

}

void diplayDigitBlue(int digit){
	
	switch (digit)
	{
		case 0 ://display 0
		PORTC &=~((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		PORTB &=~((1<<5));
		PORTC |=((1<<1));
		break;
		
		case 1 ://display 1
		PORTC &=~((1<<0)|(1<<2));
		PORTC |=((1<<1)|(1<<3)|(1<<4)|(1<<5));
		PORTB |=((1<<5));
		break;
		
		case 2 ://display 2
		PORTC &=~((1<<0)|(1<<1)|(1<<3)|(1<<4));
		PORTC |=((1<<2)|(1<<5));
		PORTB &=~((1<<5));
		break;
		
		case 3 ://display 3
		PORTC &=~((1<<0)|(1<<1)|(1<<2)|(1<<3));
		PORTC |=((1<<4)|(1<<5));
		PORTB &=~((1<<5));
		break;
		
		case 4 ://display 4
		PORTC &=~((1<<0)|(1<<1)|(1<<2)|(1<<5));
		PORTC |=((1<<3)|(1<<4));
		PORTB |=((1<<5));
		break;
		
		case 5 ://display digit 5
		PORTC &=~((1<<1)|(1<<2)|(1<<3)|(1<<5));
		PORTC |=((1<<0)|(1<<4));
		PORTB &=~((1<<5));
		break;
		
		case 6 ://display 6
		PORTC &=~((1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		PORTC |=((1<<0));
		PORTB &=~((1<<5));
		break;
		
		case 7 : //display 7
		PORTC &=~((1<<0)|(1<<2));
		PORTC |=((1<<1)|(1<<3)|(1<<4)|(1<<5));
		PORTB &=~((1<<5));
		break;
		
		case 8 ://display 8
		PORTC &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		PORTB &=~((1<<5));
		break;
		
		case 9 ://display 9
		PORTC &=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5));
		PORTC |=((1<<4));
		PORTB &=~((1<<5));
		break;
	}
	
}


void displayDigitsRed(int digit){
	
	
	switch (digit)
	{
	//0
	case 0 :
	PORTD &=~((1<<4)|(1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<2));
	PORTB |= ((1<<1));
	break;
	//1
	case 1 :
	PORTD |=((1<<4)|(1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<2));
	PORTB |= ((1<<1));
	break;
	//2
	case 2 :
	PORTD &=~((1<<4)|(1<<6)|(1<<7));
	PORTD |=((1<<5));
	PORTB &=~((1<<1)|(1<<2));
	PORTB |= ((1<<0));
    break;
	//3
	case 3 : 
	PORTD &=~((1<<4)|(1<<7));
	PORTD |=((1<<5)|(1<<6));
	PORTB &=~((1<<0)|(1<<2)|(1<<3));
	break;
	
	//4
	case 4 :
	PORTD &=~((1<<5));
	PORTD |=((1<<4)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<1)|(1<<2));
	break;
	
	//5
	case 5 :
	PORTD &=~((1<<4)|(1<<5)|(1<<7));
	PORTD |=((1<<6));
	PORTB &=~((1<<0)|(1<<1));
	PORTB |= ((1<<2));
	break;
	
	//6
	case 6 :
	PORTD &=~((1<<4)|(1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<1));
	PORTB |= ((1<<2));
	break;
	//7
	case 7 :
	PORTD &=~((1<<4));
	PORTD |=((1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<2));
	PORTB |= ((1<<1));
	break;
	
	
	//8
	case 8 :
	PORTD &=~((1<<4)|(1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<1)|(1<<2));
	break;
	
	//9
	case 9 :
	PORTD &=~((1<<4)|(1<<5)|(1<<7));
	PORTD |=(1<<6);
	PORTB &=~((1<<0)|(1<<1)|(1<<2));
	break;
		
		
	}
	
}

void buttonClickedRed(){
	
	
	//read the state of the  red interrupt pin 
	readPinSourceRed = digitalRead(INTERRUPTPINRED);

	if (readPinSourceRed == 0 ){
		
		stateRed = true;
		//count the number of clicks 
		countClickNumberRed += 1 ;
		
		if( countClickNumberRed == 10){
			
			countClickNumberRed = 0;	
		}
	}
}


void buttonClickedBlue(){
	
	//read the state of the  blue interrupt pin 
	readPinSourceBlue = digitalRead(INTERRUPTPINBLUE);

	if (readPinSourceBlue == 0 ){
		
		stateBlue = true;
		
		//count the number of the clicks
		countClickNumberBlue += 1 ;
		
		if( countClickNumberBlue == 10){
			
			countClickNumberBlue = 0;	
		}
	}
}

// the loop function runs over and over again forever
void loop() {
	
	//display digit 0 at the start in red  7 segment display 
	if(!stateRed){
	PORTD &=~((1<<4)|(1<<5)|(1<<6)|(1<<7));
	PORTB &=~((1<<0)|(1<<2));
	PORTB |= ((1<<1));
	}
	
   //display digit 0 at the start in red  7 segment display 
	if (!stateBlue){
		PORTC &=~((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		PORTB &=~((1<<5));
		PORTC |=((1<<1));
	}
	
    //if the state change from false to true then we display the digit in red 7 segment display 
	if(stateRed){
		
		displayDigitsRed(countClickNumberRed);
		
		
	}
	
   //if the state change from false to true then we display the digit in blue 7 segment display
	if(stateBlue){
		diplayDigitBlue(countClickNumberBlue);
	}
	
}
