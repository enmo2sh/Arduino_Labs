
#include <SoftwareSerial.h>

const int pot_pin = A0;
const int led_pin = 13;
const int buzzer_pin = 10;
int voltage_read;
float voltage_value;
int flag = 0;

void setup() {
  
pinMode(pot_pin,INPUT);
pinMode(led_pin,OUTPUT);
pinMode(buzzer_pin,OUTPUT);
  
Serial.begin(9600);

}

 

void loop() {

voltage_read = analogRead(pot_pin);
voltage_value = (voltage_read * 5.) / 1023.;
Serial.println(voltage_value);
exceed();
delay(100);

}

void exceed(){
  if(voltage_value > 3. && flag == 0){
    flag = 1;
    digitalWrite(led_pin, HIGH);
    tone(buzzer_pin, 500);
  }
  
  else if ( voltage_value < 2.5 && flag == 1){
    flag = 0;
    digitalWrite(led_pin, LOW);
    noTone(buzzer_pin);
  }
}
