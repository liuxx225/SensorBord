#include <Servo.h>
#include <FlexiTimer2.h>
int HrPin = 7;     // potentiometer wiper (middle terminal) connected to analog pin 3                     // outside leads to ground and +5V
int val = 0;           // variable to store the value read
int human_count1,human_count2;
Servo myservo1,myservo2;  
int pos = 0; 
int last_state,now_state;
int time_count;
int i=0;
unsigned char buff[8]={0x5A,0xA5,01,00,00,00,00,01};

void state_detect()
{
  if(last_state == 0)
  {
    time_count = 10;
  }
  else
  {
    time_count = 150;
  }
  
}
void send_message()
{
    int j;
    if(last_state == 0 && now_state == 1)
    {
        buff[7] = 1; 
        for(j=0;j<8;j++)
        {
          Serial.write(buff[j]);  
        }
    } 
    if(last_state == 1 && now_state == 0)
    {
        buff[7] = 0; 
        for(j=0;j<8;j++)
         {
            Serial.write(buff[j]);  
         }
    } 
  
   
}
void flash()
{
    int j;
    int flag;
    state_detect();
    if(digitalRead(HrPin)) 
    {
      human_count1 ++;
      digitalWrite(13,HIGH);
    }
    else 
    {
      human_count2++;
      digitalWrite(13,LOW);
    }
    i++;
    if(i== time_count)
    {  
      i = 0;
      if(human_count1==0)
      {
        now_state = 0;   //there is no person
      }
      else
      {
        now_state = 1;  //there is a person
      }
      send_message();
        
      last_state = now_state;
      human_count1 = 0;
      human_count2 = 0;   
         
    }
}

void setup()
{
  FlexiTimer2::set(50, 1.0/1000, flash);
  myservo1.attach(9);  //up
  myservo2.attach(10); //lf
  myservo2.write(107);
  myservo1.write(80);
  pinMode(HrPin,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);          //  setup serial
  FlexiTimer2::start();
}

void loop()
{
  
}



