int GreenOutput =13;
int RedOutput =12;
int LdrInput=A1;
int Tempstate=0;
int out2;
int Laserinput;
void setup()
{
  Serial.begin(9600);
  pinMode(GreenOutput, OUTPUT);
  pinMode(RedOutput, OUTPUT);
  pinMode(LdrInput, INPUT);
}

void loop()
{
   delay(6000);
  int scaninput=analogRead(LdrInput);
  if(Serial.available() >0){
      Laserinput=Serial.parseInt();
      Serial.print("the output of state machine:");
      Serial.println(Laserinput);
      delay(2000);
  }
  Checker(scaninput,Laserinput);
  delay(6000); // Wait for 1000 millisecond(s)
}
void Checker(int input,int out1){
  if (Tempstate==0&&input<512){
     out2=0;
  }else if (Tempstate==0&&input>512){
    Tempstate=1;
    out2=0;
  }else if (Tempstate==1&&input<512){
    out2=0;
  }else if (Tempstate==1&&input>512){
    out2=1;
    Tempstate=0;
  }
  Serial.print("the expected output:");
  Serial.println(out2);
  if(out1==out2){
    Serial.println("true");
    digitalWrite (RedOutput,LOW);
    digitalWrite (GreenOutput,HIGH);
  }
  else {
    Serial.println("false");
    digitalWrite (GreenOutput,LOW);
    digitalWrite (RedOutput,HIGH);
  }    
}
