//We always have to include the library
#include "LedControl.h"


LedControl lc=LedControl(12,11,10,4);
boolean ON = true;
boolean OFF = false;


void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  lc.setIntensity(1,8);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void loop(){
String info = "(0,0),(0,1),(0,2),(1,2),(1,3),(2,3)";
  Serial.begin(9600);

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

    //set LED on
    Serial.print(row);
    Serial.print(" ");
    Serial.print(col);
    one_init();

    lc.setLed(0, row, col, ON);
    delay(1000);
    
   }

   delay(3000);
   lc.clearDisplay(0);
   lc.clearDisplay(1);
   delay(1000);
  
}
