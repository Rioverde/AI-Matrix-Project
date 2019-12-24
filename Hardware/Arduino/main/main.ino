 //We always have to include the library
#include "LedControl.h"
#include "SoftwareSerial.h"


LedControl lc=LedControl(12,11,10,4);
boolean ON = true;
boolean OFF = false;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    Serial.begin(9600);
}


void loop(){
  if (Serial.available() > 0){
  Serial.println("Connected");
  String info;
  char c;
  while (c = Serial.read()) {
      info += c;
    }
  Serial.println(info);

  //parcing document in arduino
  for(int i = 0; i < info.length(); i++) {
    int row = 0, col = 0;                                                                                                                                                        

    if(info[i] == '#'){
      lc.clearDisplay(0);
      break;
    }
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

    lc.setLed(0, row, col, ON);
    delay(1000);

    //If u want to pixel travel
    lc.setLed(0, row, col, OFF);
    
   }
  }

  else
    Serial.println("Error in Connection: Serial is not available");

   delay(3000);
   lc.clearDisplay(0);
   delay(1000);
}