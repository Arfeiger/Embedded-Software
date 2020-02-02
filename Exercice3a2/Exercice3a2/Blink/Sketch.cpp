/*
  author  : Mechenane Khalef 
  Date    : 22/10/2019
  version : 1.0
  Description : Use the 1k NTC thermistor to measure the temperature inside the room.
  
*/

#include <Arduino.h>


#define analogPin 0 
#define sizeOfTable 32

//Struct for the Look-up-Table 

typedef struct {
	
	float adcValue ;
	float temperatureValue;
	
} lookUpTable;


float adcValueToTemperature(lookUpTable *table, int lookUpTableSize, float analogValue);


//the setup function runs once when you press reset or power the board

void setup() {
	
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


// The given look up table 
lookUpTable myLookUpTable [sizeOfTable] = {

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

//the loop function runs over and over again forever

void loop() {
	
volatile float analogValue = 0 ;	
volatile float resultTemperature = 0 ;
analogValue = analogRead(analogPin) ;

resultTemperature = adcValueToTemperature(myLookUpTable , sizeOfTable , analogValue);

}
