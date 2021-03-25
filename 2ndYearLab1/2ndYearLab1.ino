#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int A;
int B ;
int result;
String opCode;
String oper;
int Button1=6;
int Button2=7;
int swState1,swState2;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(Button1,INPUT_PULLUP);
  pinMode(Button2,INPUT_PULLUP);

}

void loop() {
    if(Serial.available() >0){
    A=Serial.parseInt();
      Serial.println(A);
      delay(2000);
    B=Serial.parseInt();
      Serial.println(B);
      delay(2000);
    opCode=Serial.readString();
    delay(2000);
      Serial.println(opCode);
    Call(opCode,A,B);
    delay(3000);
    lcd.clear();
  }
  swState1=digitalRead(Button1);
  swState2=digitalRead(Button2);
  
  if(swState1==LOW){
  lcd.print("up");
   }
  if(swState2==LOW){
    lcd.print("down");
   }
  while(swState1==LOW) {
      swState1=digitalRead(Button1);
      delay(10);
      }
  while(swState2==LOW){
      swState2=digitalRead(Button2);
      delay(10);
      }
}
void Call(String opCode,int A,int B){
  int result;
  //if(opCode.equals("000"))
  if(opCode.equals("001"))
    result=sub(A,B);
  //else if(opCode.equals("010"))
  else if(opCode.equals("011"))
    result=ShiftRightUnsign(A,B);
  else if(opCode.equals("100"))
    result=FunctionShiftSign(A,B);
  //else if(opCode.equals("101"))
  else if(opCode.equals("110"))
    result=Or(A,B);
  else if (opCode.equals("111"))
    result=FunctionXOR(A,B);
  else {
    lcd.println("ERROR");
    return;
  }
  lcd.print(A);
  lcd.print(oper);
  lcd.print(B);
  lcd.print("=");
  lcd.print(result); 
}
int sub (int A,int B){
  oper="-";
  return A-B;
}
int Or(int A,int B){
  oper="|";
return A|B;
}
int ShiftRightUnsign(int A,int B){
  oper=">>unsigned";
  return A>>(abs(B));
}
int FunctionXOR(int A,int B) {
  oper="^";
 int output= A ^ B;
 return output;
}
int FunctionShiftSign(int A,int B) {
  oper=">>signed";
 int output= A >> B;
 return output;
}
    
