// include the library code for LCD:
#include <LiquidCrystal.h>

int switch1 = A0, switch2 = A1; // initialize pins for switches
int sw1value, sw2value,x = 1, m = 0;

String welcome = "Stopwatch by Abin";

int stringStart, stringStop = 0;   //variables to allow scrolling
int scrollCursor = 8;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(8, 2);
  lcd.print("Welcome"); //print message to LCD
  Serial.begin(9600);
}

void loop() {
  sw1value = analogRead(switch1);  //Read values from switch
  sw2value = analogRead(switch2);
  
  Serial.print("sw1:");    //Print inputs of switches to Serial Monitor
  Serial.print(sw1value);  //Switch Start/Pause
  Serial.print(" sw2:");
  Serial.println(sw2value);//Switch Resume/Reset
  
  lcd.setCursor(0,0);
  lcd.print("Welcome"); //Start screen
  
  //If "Start" is pressed
  if(sw1value > 0 && sw2value == 0)
  {
    //infinite loop
    do{
    
      //code to scroll just first line of LCD
    for(int i=0; i <= 59; i++){
      lcd.setCursor(scrollCursor, 0);
      lcd.print(welcome.substring(stringStart,stringStop));
      delay(300);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(m); // re-print minutes, as lcd was cleared
      if(stringStart == 0 && scrollCursor > 0){
       scrollCursor--;
    stringStop++;
  } else if (stringStart == stringStop){
    stringStart = stringStop = 0;
    scrollCursor = 8;
  } else if (stringStop == welcome.length() && scrollCursor == 0) {
    stringStart++;
  } else {
    stringStart++;
    stringStop++;
  }
  //if seconds reach "59" add "1" to minutes
      if(i >=59)
      {
        m= m+1;
        lcd.setCursor(0,1);
        lcd.print(m);
       }
     
    lcd.setCursor(2,1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    lcd.print(i);
  
    sw2value = analogRead(switch2); //read switch values
    sw1value = analogRead(switch1);
    
    Serial.print("sw1:");
    Serial.print(sw1value);
    Serial.print("sw2:");
    Serial.println(sw2value);
    
    //if "Reset" is pressed Break loop
    //if "Pause" is pressed, pause code until "Resume" is pressed
    if(sw2value > 0){
      Serial.println("break");
      lcd.clear();
      break;
    }    
    else if(sw1value > 0)
    {
      do{
        Serial.println("pause");
        sw2value = analogRead(switch2);
        if(sw2value > 0)
        {
          delay(1000);
          m = 0;
          break;
        }
      }while(x > 0);
    }
    
    delay(700); //delay of 0.7s; 0.3s from start of code total delay = 1s
  }
  }while(x > 0 && sw2value == 0);
  }
  }

