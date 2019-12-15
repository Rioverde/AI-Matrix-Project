#include "LedControl.h"
LedControl lc=LedControl(12,11,10,4);
boolean ON = true;
boolean OFF = false;


byte one[] =
{
  B00000000,
  B00011000,
  B00111000,
  B00011000,
  B00011000,
  B00011000,
  B00111100,two
  B00000000
};


byte two[] =
{
  B00000000,
  B00011000,
  B00100100,
  B00001100,
  B00011000,
  B00110000,
  B00111100,
  B00000000
};

byte three[] =
{
  B00000000,
  B00011000,
  B00100100,
  B00001100,
  B00011000,
  B00110000,
  B00111100,
  B00000000
};

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

int counter = 1;
void loop(){
String info = "(0,0),(0,1),(0,2),(1,2),(1,3),m(2,3),(1,5),(1,6)";
  Serial.begin(9600);

  //parcing document in arduino
  for(int i = 0; i < info.length(); i++) {
    int row = 0, col = 0;                                                                                                                                                        

    if(counter == 1){
        digit_init();
        }
    if(info[i] == 'm'){
      counter++;
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      
      if(counter == 2){
        digit_init2();
        continue;
        }

      if(counter == 3){
        digit_init3();
        continue;
        }
   
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
    
   }

   delay(2000);
   lc.clearDisplay(0);
   lc.clearDisplay(1);
   delay(2000);
   counter = 1;
  
}

void digit_init()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,one[i]);
  }

}

void digit_init2()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,two[i]);
  }

}

void digit_init3()
{
     for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,three[i]);
  } 
}
