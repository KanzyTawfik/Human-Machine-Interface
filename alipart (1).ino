#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "ADC.h" 

#define buzzer 3 //buzzer variable set as pin 3

void init(){
Adc_Init(); // initilize ADC
LCD_Init (); // initilize LCD
DIO_init(); //initilize inputs/outputs (buzzer as output) 
}

int main(void){
init();     
  
  int mintemp = 20;  // setting max temperature max 
   int maxtemp = 40; // setting max temperature max 
  char tempstr[5]; // string buffer to convert num to string

//while loop start
  while (1)
  {
    int  button = Adc_ReadChannel(0); // reads analogue input at channel 0 (button pressed on LCD keypad)
    float tempC = Adc_ReadChannel(1)/3.8; // reads analogue input at channel 1 (temperature sensor)
		 
    LCD_Clear(); //clears LCD