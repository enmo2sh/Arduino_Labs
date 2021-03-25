int ldr =A0;
int input,out;
int state=0;
void setup(){
  Serial.begin(9600);
  pinMode(ldr, INPUT);
}

void loop(){
  delay(5000);
  input = analogRead(ldr);
  Serial.println(input);
  int output=stateMachine(input); 
  Serial.print("the output of state machine:");
  Serial.println(output);
  delay(6000);
}
int stateMachine(int input){
  if (state==0&&input<512){
     out=0;
  }else if (state==0&&input>512){
    state=1;
    out=0;
  }else if (state==1&&input<512){
    out=0;
  }else if (state==1&&input>512){
    out=1;
    state=0;
  }
  return out;
}
