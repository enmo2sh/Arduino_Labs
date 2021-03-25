#include <SoftwareSerial.h>
const int led_pin = 2;
const int buzz_pin = 3;
const int lm35 = A0;
float temp ;
void setup() {
  pinMode(led_pin,OUTPUT);
  pinMode(buzz_pin,OUTPUT);
  pinMode(lm35,INPUT);
  Serial.begin(9600);

}

void loop() {
  temp = analogRead(lm35);
  temp *= 0.48828125;
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" C ");
  if(temp > 30){
    digitalWrite(led_pin, HIGH);
    tone(buzz_pin, 500);
  }
  else {
    digitalWrite(led_pin, LOW);
    noTone(buzz_pin);
  }
  delay(250);

}
