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

    // if statement for changing max and min buttons on lcd
      if (button < 100){ 
        mintemp ++;  //right button increases min temperature temp threshold
        LCD_String_xy (0, 1, mintemp); //print new min value (+1)
      }
      else if (button < 200) {
        maxtemp ++;  // up button increases max temperature temp threshold
         LCD_String_xy (0, 1,maxtemp); //print new max value (+1)
      }
      else if (button < 400){
        maxtemp --;  //down button decreases max temperature temp threshold
         LCD_String_xy (0, 1, maxtemp); //print new max value (-1)
      }  
        else if (button < 600){
        mintemp --;  //left button decreases max temperature temp threshold
         LCD_String_xy (0, 1, mintemp); //print new min value (-1)
        }

    if (tempC > maxtemp || tempC < mintemp){ //if statement for temperature values if max or min values are exceeded
      DIO_SetPinDirection('d', 3, 'h');
      PORTD |= _BV(PORTD3); // buzzer on
    }
    else { //temrature value stays between limits
        DIO_SetPinState('d', 3, 'l');
        PORTD &= ~_BV(PORTD3); // buzzer off 
    }


    tostring(tempstr, tempC);
    
    LCD_String_xy (0, 0, "Temp: "); // prints "Temp: " at row 0 and column 0
    LCD_String_xy (0, 8, tempstr);
    LCD_String_xy(0, 11 ,"C");
    
    tostring(tempstr, mintemp);
    
    LCD_String_xy (1, 0, "Min:"); // prints "Min:" at row 1 and column 8
    LCD_String_xy (1, 4, tempstr); // prints temperature min at row 1 and column 12
    
    tostring(tempstr, maxtemp);
    
    LCD_String_xy (1, 8, "Max:"); // prints "Max:" at row 1 and column 0
    LCD_String_xy (1, 12, tempstr); // prints temperature max at row 1 and column 4

     
    _delay_ms(500);
  }

  return 0; 
}


