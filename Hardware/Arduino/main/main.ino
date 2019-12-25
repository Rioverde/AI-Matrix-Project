#include <LedControl.h>
#include <SoftwareSerial.h>



byte one[] =
{
  B00000000,
  B00011000,
  B00111000,
  B00011000,
  B00011000,
  B00011000,
  B00111100,
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
  B00001000,
  B00000100,
  B00100100,
  B00011000,
  B00000000
};

byte four[] =
{
  B00000000,
  B00001100,
  B00010100,
  B00100100,
  B00111100,
  B00000100,
  B00000100,
  B00000000
};

byte def[] =
{
  B00000000,
  B00000000,
  B00110010,
  B01001010,
  B01111010,
  B01001010,
  B01001010,
  B00000000
};


byte done[] =
{
  B00000000,
  B00000001,
  B00000011,
  B00000110,
  B10001100,
  B11011000,
  B01110000,
  B00100000
};






//Test
//(0,0),(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7)
LedControl lc=LedControl(12,11,10,4);
boolean ON = true;
boolean OFF = false;
int flag = 0;

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
  Serial.begin(115200);

}

String info;
int row = 0, col = 0;

void loop(){

  if (Serial.available()){
    Serial.println("Connected");
    info = Serial.readStringUntil('#');
    Serial.println(info);
  } 
  if (!Serial.available()){
      Serial.println("Send Data");
      defv();
      delay(1000);
}

  //parcing document in arduino
  for(int i = 0; i < info.length(); i++) {                                                                                                                                                        

    if(info[i] == '#'){
      lc.clearDisplay(0);
      flag++;
    }
    
    if(info[i] == '|'){
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      delay(1000);
      flag++;
      continue;
    }
    
    if(info[i] == ' ') {
      ++i;
      continue;
    }
    
    if(info[i] == '(') {
      ++i;

      if(isDigit(info[i])) {
        row = info[i] - '0';
      }
      ++i;

      if(info[i] == ',') {
        ++i;
        if(isDigit(info[i])) {
          col = info[i] - '0';
        }
        ++i;
          if(info[i] == ')') {
          ++i;
          }
        }
      }
      
    switch(flag){
      case 0:
        one_init();
        break;
      case 1:
        two_init();
        break;
      case 2:
        tree_init();
        break;
      case 3:
        four_init();
        break;
      default:
        break;
    }

    //Light up Led with given Row and Column
    lc.setLed(0, row, col, ON);
    delay(1000);
  }
  
  //Clean Display

  flag = 0;
  delay(1000);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  delay(1000);
}

void one_init()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,one[i]);
  }
}

void two_init()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,two[i]);
  }
}

void tree_init()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,three[i]);
  }
}

void four_init()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,four[i]);
  }
}

void defv()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,def[i]);
  }
}

void donef()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,done[i]);
  }
}


