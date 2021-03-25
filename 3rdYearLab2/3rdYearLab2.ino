#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    int num1=Serial.parseInt();
    // while loops can be used instead of delay to let the user enters the number 
    // but with one issue if the user wants to enter zero 
   // while(num1==0)
     // num1=Serial.parseInt();
    Serial.println(num1);
    delay(2000);
    int num2=Serial.parseInt();
    //while(num2==0)
      //num2=Serial.parseInt();
    Serial.println(num2);
    int result=num1+num2;
    Serial.println(result);
    delay(2000);
  }
}
