 //We always have to include the library
#include "LedControl.h"
#include "SoftwareSerial.h"
#define SERIAL_BUFFER_SIZE 256


//Test
//(0,0),(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7)
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
  Serial.begin(115200);

}

String info;
int row = 0, col = 0;

void loop(){

  if (Serial.available()){
    Serial.println("Connected");
    info = Serial.readStringUntil('#');
    Serial.println(info);
  } else
      Serial.println("Error: Serial Connection is not available");

  //parcing document in arduino
  for(int i = 0; i < info.length(); i++) {                                                                                                                                                        

    if(info[i] == '#'){
      lc.clearDisplay(0);
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
        row = info[i] - '0';
        Coordinates += row;
      }
      ++i;

      if(info[i] == ',') {
        ++i;
        if(isDigit(info[i])) {
          col = info[i] - '0';
          Coordinates += col;
        }
        ++i;
          if(info[i] == ')') {
          ++i;
          }
        }
      }
      
    //Light up Led with given Row and Column
    lc.setLed(0, row, col, ON);
    delay(2000);

  }
  
  //Clean Display
  delay(1000);
  lc.clearDisplay(0);
  delay(1000);

}