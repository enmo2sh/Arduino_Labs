#include <SoftwareSerial.h>
 
int led_pin = 5 ;
char *letters[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};//A-Z
char *Numbers[]={"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."}; //0-9
int gap_unit = 500;
void setup()
{
  // put your setup code here, to run once:
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  // put your main code here, to run repeatedly:
  char serial_read;
  if(Serial.available())
  {
    serial_read = Serial.read();
    if (serial_read >= 'a' && serial_read <= 'z')
      {
        letters_of_one_word (letters[serial_read-'a']);
      }
    else if (serial_read >= 'A' && serial_read <= 'Z')
      {
        letters_of_one_word (letters[serial_read-'A']);
      }
    else if (serial_read >= '0' && serial_read <= '9')
      {
        letters_of_one_word (Numbers[serial_read-'0']);
      }
    else if (serial_read == ' ')
      {
        delay(gap_unit * 7);
      }
  }
}
 
void letters_of_one_word (char *temp)
{
  int i=0 ;
  while ( temp[i] != NULL )
  {
    dot_dash_blink (temp[i]);
    i++;
  }
   delay (gap_unit*3);
}
/* a function to control led blinking for dash and dot */
void dot_dash_blink ( char sympol )
{
  digitalWrite(led_pin,HIGH);
  if (sympol == '.')
  {
    delay(gap_unit);
    digitalWrite (led_pin,LOW);
    delay(gap_unit);
  }
  /* input is '-' */
  else
  {
    delay(gap_unit*3);
    digitalWrite (led_pin,LOW);
    delay(gap_unit);
  }
 
}
