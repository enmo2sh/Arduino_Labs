const int red=3;
const int green=4;
const int button=5;
int buttonState=0;
int states[]={0,1};
unsigned long oldtime=0;
unsigned long newtime=0;
void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(button,INPUT);
}
 
void loop() {
  digitalWrite(red,states[0]);
  digitalWrite(green,states[1]);
  newtime=millis()/1000;
  buttonState=digitalRead(button);
  if(((newtime-oldtime)==2)||(buttonState==HIGH)){
    swap();
    oldtime=newtime;
    while(buttonState)
      buttonState=digitalRead(button);
  }
}
void swap(){
  int temp=states[0];
  states[0]=states[1];
  states[1]=temp;
}
