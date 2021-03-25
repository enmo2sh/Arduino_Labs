#include <IRremote.h>
int IR_RECEIVE_PIN = 10;
IRrecv IrReceiver(IR_RECEIVE_PIN);
decode_results results;
int time=100;
int red_pin=12;
int button = 0;

void setup() {
    Serial.begin(9600);
    IrReceiver.enableIRIn();
    pinMode(red_pin,OUTPUT);
}

void loop() {
    if (IrReceiver.decode(&results)) {
        //Serial.println(results.value,HEX);
        IrReceiver.resume();
    getButton();
        Serial.print("button = ");
        Serial.println(button);
    }
  if(button == 0)
    digitalWrite(red_pin,LOW);
  else
    blink();
}

void getButton(){
  if(results.value==0xFD08F7)
        button=1;
  else if(results.value==0xFD8877)
        button=2;
  else if(results.value==0xFD48B7)
        button=3;
  else if(results.value==0xFD28D7)
        button=4;
  else if(results.value==0xFDA857)
        button=5;
  else if(results.value==0xFD6897)
        button=6;
  else if(results.value==0xFD18E7)
        button=7;
  else if(results.value==0xFD9867)
        button=8;
  else if(results.value==0xFD58A7)
        button=9;
  else if(results.value==0xFD30CF)
      button=0;
}
void blink(){
    digitalWrite(red_pin,HIGH);
    delay(time*button);
    digitalWrite(red_pin,LOW);
    delay(time*button);
}
