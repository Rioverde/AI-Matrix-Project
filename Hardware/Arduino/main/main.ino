//We always have to include the library
#include "LedControl.h"


//Use pins 12,11,10 and 1 MAX7219
// Pins: DIN,CLK,CS, # of Display connected
LedControl lc=LedControl(12,11,10,4);

boolean ON = true;
boolean OFF = false;

//Set brightness
lc.setIntensity(0,8);
//Waking up the module
lc.shutdown(0,false);

void setup(){
  Serial.begin(9600);
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop(){

//listen and connect to PC 
  if (Serial.available() > 0){
	String info;
	info = SerialStringUntill('#');
	Serial.Print(info);

	//parcing document in arduino
	for(int i = 0; i < info.length(); i++) {
	  int row = 0, col = 0;                                                       

	  if(info[i] == '\n'){
		  lc.clearDisplay(0);
		  delay(3000);
	  }
		
		if(info[i] == ' ') {
			++i;
			continue;
		}
		if(info[i] == '(') {
			++i;

			if(isDigit(info[i])) {
				Serial.println(info[i]);
				row = (int)info[i] - 48;
			}
			++i;

			if(info[i] == ',') {
				++i;
				if(isDigit(info[i])) {
					Serial.println(info[i]);
					col = (int)info[i] - 48; 
				}
				++i;
					if(info[i] == ')') {
					++i;
					}
				}
			}
					// Set LED on
					Serial.print(row);
					Serial.print(" ");
					Serial.print(col);

					ls.setLed(0, row, col, ON);
					delay(1000);

					// Option to do it pixel by pixel
					ls.setLed(0, row, col, OFF);
		}

					delay(2000);
					lc.clearDisplay(0);
					delay(2000);
	}

	else	
		Serial.Println("Connection Error: Check your port name in C++ code")

}
