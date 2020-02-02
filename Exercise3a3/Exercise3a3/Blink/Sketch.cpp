/*
  author  : Mechenane Khalef 
  Date    : 22/10/2019
  version : 1.0
  description : Display the digits from the temperature .
  
*/

#include <Arduino.h>


#define ANALOGPIN 0 
#define SIZEOFTable 32
#define TIMES 3
#define DELAYS 2000

//Define pins to the leds

#define APIN 2
#define BPIN 8
#define CPIN 6
#define DPIN 5
#define FPIN 3
#define EPIN 4
#define GPIN 7

// Struct for the Look-up-Table 

typedef struct {
	
	float adcValue ;
	float temperatureValue;
	
} lookUpTable ;

void turnAllOff();
void turnAllOn();
void digitsSegmentsCase(int digit);
float adcValueToTemperature(lookUpTable *table, int lookUpTableSize, float analogValue);
void  displayDigits(float temperatureValue);
void clockwise(int times);
void showThreeandE(int times);

//the setup function runs once when you press reset or power the board

void setup() {
	
	//Initialize digital pins from 2-8 as outputs.
	
	pinMode(APIN, OUTPUT);
	pinMode(BPIN, OUTPUT);
	pinMode(CPIN, OUTPUT);
	pinMode(DPIN, OUTPUT);
	pinMode(EPIN, OUTPUT);
	pinMode(FPIN, OUTPUT);
	pinMode(GPIN, OUTPUT);
	
}

// convert the adc values to real temperature

float adcValueToTemperature(lookUpTable *table, int lookUpTableSize, float analogValue) {

	volatile float temperatureFound = 0;
	volatile float temperatureCalcul = 0;

	bool adcValueFound = false;

	for (int i = 0; i <= lookUpTableSize; i++) {
		
		
        // the case where adc value was found in the look up table 
		
		if (analogValue == table[i].adcValue) {

			temperatureFound = table[i].temperatureValue;

			adcValueFound = true;

		}
		else
		
		// if the adc value was found in the look up table we calculate the slope 
		
	    	if  (analogValue < table[i].adcValue)  {

			  volatile float slote = (table[i].temperatureValue - table[i - 1].temperatureValue) / (table[i].adcValue - table[i - 1].adcValue);
 
			  temperatureCalcul = slote * (analogValue - table[i].adcValue) + table[i].temperatureValue;
			  
			  break;
		    }
	} 

	if (adcValueFound)
	  return temperatureFound;
	else
	  return temperatureCalcul;

}

// Display digits depending in the parameter

void digitsSegmentsCase(int digit) {

	switch (digit)
	{
		case 0 :
		PORTB = B11111110;// Displaying Number 0
		PORTD = B10000011;
	    break;
		case 1 :
		PORTB = B11111110;//Displaying Number 1
		PORTD = B10111111; 
		break;
		case 2 :
		PORTB = B11111110;//Displaying Number 2
		PORTD = B01001011; 
		break;
		case 3 :
		PORTB = B11111110; //Displaying Number 3
		PORTD = B00011011;
		break;
		case 4 :
		PORTB = B11111110;//Displaying Number 4
		PORTD = B00110111; 
		break;
		case 5 :
		PORTD = B00010011;//Displaying Number 5
		PORTB = B11111111;
		break;
		case 6 :
		PORTD = B00000011;// Displaying Number 6
		PORTB = B11111111;
		break;
		case 7 :
		PORTB = B11111110;//Displaying Number 7
		PORTD = B10111011; 
		break;
		case 8 :
		PORTB = B11111110;//Displaying Number 8
		PORTD = B00000011;
		break;
		case 9 :
		PORTB = B11111110;//Displaying Number 9
		PORTD = B00010011;
		break;
	}
}
//Display the temperature digits in the 7 segments

void  displayDigits(float temperatureValue) {
	
	//convert the temperature which is a float to an int 
	
	int temperatureRounded = (int) temperatureValue;
	
    //if the temperature has one digit
	if (temperatureRounded < 10) {
		
		digitsSegmentsCase(temperatureRounded);
		delay(DELAYS);
		turnAllOff();
		delay(DELAYS);
	}
	
    // if the temperature has two digits 
	
	if (10 <= temperatureRounded && temperatureRounded < 100) {
        
		//extract the first digit 
		
		int firstdigit = temperatureRounded / 10;
	     digitsSegmentsCase(firstdigit);
		 delay(DELAYS);
		 turnAllOff();
		 //extract the second digit 
		int secondDigit = temperatureRounded % 10;
		delay(DELAYS); 
		digitsSegmentsCase(secondDigit);	
    	delay(DELAYS);
		
		}
	//if the temperature has three digits 
	if (100 <= temperatureRounded  && temperatureRounded < 1000) {
       //extract the first digit
		int firstdigit = temperatureRounded / 100;
		digitsSegmentsCase(firstdigit);
		delay(DELAYS);
		turnAllOff();
		delay(DELAYS);
		//extract the second digit
		int secondDigit = (temperatureRounded /10) % 10;
		digitsSegmentsCase(secondDigit);	
	    delay(DELAYS);
		turnAllOff();
		delay(DELAYS);
		//extract the third digit 
		int thirdDigit = temperatureRounded % 10;
	    digitsSegmentsCase(thirdDigit);	
		turnAllOff();
		
		
	}

}
//blink number 3 and letter E.

void showThreeandE(int times){

  for(int i = 0; i < times; i++) {
    digitalWrite(FPIN,HIGH);
    digitalWrite(EPIN,HIGH);
    delay(1000);
    digitalWrite(FPIN,LOW);
    digitalWrite(EPIN,LOW);
    digitalWrite(BPIN,HIGH);
    digitalWrite(CPIN,HIGH);
    delay(1000);
    digitalWrite(BPIN,LOW);
    digitalWrite(CPIN,LOW);
  } 
}

//turn the light one by one clockwise.
void clockwise(int times) {

  for(int i = 0; i < times; i++) {
	  
    digitalWrite(APIN,LOW);
    delay(1000);
    digitalWrite(BPIN,LOW);
    delay(1000);
    digitalWrite(CPIN,LOW);
    delay(1000);
    digitalWrite(DPIN,LOW);
    delay(1000);
    digitalWrite(EPIN,LOW);
    delay(1000);
    digitalWrite(FPIN,LOW);
    delay(1000);
	
	//turn off all the leds 
     turnAllOff();

  }
}
// The given look up table 
lookUpTable myLookUpTable [SIZEOFTable] = {
	
{250, 1.4},
{275, 4.0},
{300, 6.4},
{325, 8.8},
{350, 11.1},
{375, 13.4},
{400, 15.6},
{425, 17.8},
{450, 20.0},
{475, 22.2},
{500, 24.4},
{525, 26.7},
{550, 29.0},
{575, 31.3},
{600, 33.7},
{625, 36.1},
{650, 38.7},
{675, 41.3},
{700, 44.1},
{725, 47.1},
{750, 50.2},
{775, 53.7},
{784, 55.0},
{825, 61.5},
{850, 66.2},
{875, 71.5},
{900, 77.9},
{925, 85.7},
{937, 90.3},
{950, 96.0},
{975, 111.2},
{1000, 139.5}
	
};

//Turn off all lights.

void turnAllOff(){
	
	digitalWrite(APIN,HIGH);
	digitalWrite(BPIN,HIGH);
	digitalWrite(CPIN,HIGH);
	digitalWrite(DPIN,HIGH);
	digitalWrite(EPIN,HIGH);
	digitalWrite(FPIN,HIGH);
	digitalWrite(GPIN,HIGH);
}

//Turn on all lights.

void turnAllOn(){
	
	digitalWrite(APIN,LOW);
	digitalWrite(BPIN,LOW);
	digitalWrite(CPIN,LOW);
	digitalWrite(DPIN,LOW);
	digitalWrite(EPIN,LOW);
	digitalWrite(FPIN,LOW);
	digitalWrite(GPIN,LOW);
}

//the loop function runs over and over again forever

void loop() {
	
volatile float analogValue = 0 ;	
volatile float resultTemperature = 0 ;
analogValue = analogRead(ANALOGPIN) ;
resultTemperature = adcValueToTemperature(myLookUpTable ,SIZEOFTable ,analogValue);
showThreeandE(TIMES);
turnAllOff();
delay(DELAYS);
displayDigits(resultTemperature);
turnAllOff();
delay(DELAYS);
clockwise(TIMES);
delay(DELAYS);
turnAllOn();

}
