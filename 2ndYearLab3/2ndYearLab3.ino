#include <LiquidCrystal.h>
int seconds=0;
int minutes=0;
int hours=0;
String current="A";
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String clock[10]={"0","0",":","0","0",":","0","0","A","M"};
String Alarm[10];
const int UpButton = 8 ,DownButton = 9,RightButton = 6,LeftButton = 7,SelectButton = 13,AlarmButton =10;         
int UpState = 0,DownState = 0,RightState = 0,LeftState = 0,SelectState = 0,AlarmState=0;             
boolean setmode=false , alarm=false,select=false;
 
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(UpButton, INPUT);
  pinMode(DownButton, INPUT);
  pinMode(RightButton, INPUT);
  pinMode(LeftButton, INPUT);
  pinMode(SelectButton, INPUT);
  print();
}
 
void loop() {
  Timer();
  SelectState = digitalRead(SelectButton);
  if(SelectState==HIGH){
    setmode=true;
    select=true;
    SetMode();
  }
  loop(SelectButton,SelectState);
  AlarmState = digitalRead(AlarmButton);
  if(AlarmState==HIGH){
    setmode=true;
    alarm=true;
    SetMode();
  }
  loop(AlarmButton,AlarmState);
  
}
void Timer(){
  seconds=seconds+1;
  if(seconds>=59){
    seconds=0;
    if(minutes==59){
     minutes=0;
    if(hours==11){
      hours=0;
      if(clock[8].equals("A"))
       clock[8]="P";
      else
        clock[8]="A"; 
      current=clock[8];
    }
    else
       hours++;
  }
  else
    minutes++;
 
  }
  Save(hours,0);
  Save(minutes,3);
  Save(seconds,6);
  clock[8]=current;
  print();
  if(checkALarm() && alarm){
    lcd.clear();
    lcd.print("Alarm!!");
    delay(200);
  }
  delay(1000);
}
void Save(int num,int idx){
  if(num<10){
    clock[idx]="0";
    clock[idx+1]=String(num);
  }
  else{
    clock[idx]=String(num/10);
    clock[idx+1]=String(num%10);
  } 
}
void print(){
  lcd.setCursor(0, 0);
  for(int i=0;i<10;i++)
    lcd.print(clock[i]);
}
void SetMode(){
  int idx=-1;
  int old=0;
  while(setmode){
    UpState = digitalRead(UpButton);
    DownState = digitalRead(DownButton);
    RightState = digitalRead(RightButton);
    LeftState = digitalRead(LeftButton);
    while(UpState==LOW&&DownState==LOW&&RightState==LOW&&LeftState==LOW){
      UpState = digitalRead(UpButton);
      DownState = digitalRead(DownButton);
      RightState = digitalRead(RightButton);
      LeftState = digitalRead(LeftButton);
      delay(10);
    }
    if(RightState==HIGH){
      old=idx;
      idx++;
      if(idx<9){
          if(clock[idx].equals(":"))
              idx++;
       }
      else{ //end set mode
        endSetMode();
        setmode=false;
      }
      loop(RightButton,RightState);
    }
    if(LeftState==HIGH){
      old=idx;
      if(idx>0){
        idx--;
        if(clock[idx].equals(":"))
              idx--;
       }
      loop(LeftButton,LeftState);
    }
    if(UpState==HIGH){
      increment(idx);
      loop(UpButton,UpState);
    }
    if(DownState==HIGH){
      decrement(idx);
      loop(DownButton,DownState);
    }
    putDash(old,idx);
  }
}
void loop(int button,int buttonState){
  while(buttonState==HIGH) {
        buttonState = digitalRead(button);
          delay(10);
      }
}
void increment(int idx){
  if(idx>-1){
    if((idx==0 &&(clock[idx].toInt())<1)||(idx==1 &&(clock[idx].toInt())<1)||(idx==3 &&(clock[idx].toInt())<5)||(idx==4 &&(clock[idx].toInt())<9)||(idx==6 &&(clock[idx].toInt())<5)||(idx==7 &&(clock[idx].toInt())<9))
      clock[idx]=String(clock[idx].toInt()+1);
    else if (idx==8 &&clock[idx].equals("A"))
      clock[idx]="P";
    else if (idx==8 &&clock[idx].equals("P"))
      clock[idx]="A";  
    print();
  }
}
void decrement(int idx){
  if(idx>-1){
    if(idx<8 &&(clock[idx].toInt())>0)
      clock[idx]=String(clock[idx].toInt()-1);
    else if (idx==8 &&clock[idx].equals("A"))
      clock[idx]="P";
    else if (idx==8 &&clock[idx].equals("P"))
      clock[idx]="A"; 
    print(); 
  }
}
void putDash(int o,int n){
  lcd.setCursor(o,1);
  lcd.print(" ");
  if(o==8){
    lcd.setCursor(o+1,1);
    lcd.print(" ");
  }
  if(n<9){
    lcd.setCursor(n,1);
    lcd.print("-");
    if(n==8){
      lcd.setCursor(n+1,1);
      lcd.print("-");
    }
  }
}
void endSetMode(){
  if(select){
    hours=(clock[0].toInt())*10+clock[1].toInt();
    minutes=(clock[3].toInt())*10+clock[4].toInt();
    seconds=(clock[6].toInt())*10+clock[7].toInt();
    current=clock[8];
    select=false;
  }
  else{
    for(int i=0;i<10;i++)
      Alarm[i]=clock[i];
  }
}
boolean checkALarm(){
  boolean res=true;
  if(!alarm)
    res=false;
  if((Alarm[0].toInt()*10)+(Alarm[1].toInt())!=hours)
    res=false;
  if((Alarm[3].toInt()*10)+(Alarm[4].toInt())!=minutes)
    res=false;
  if((Alarm[6].toInt()*10)+(Alarm[7].toInt())!=seconds)
    res=false;
  if(!current.equals(Alarm[8]))
    res=false;
  
  return res;
}
 
