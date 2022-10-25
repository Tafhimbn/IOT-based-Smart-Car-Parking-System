#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
SoftwareSerial nodemcu(0,1); //SoftwareSerial mySerial(RX, TX);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int parking_slot[]={7,8,9,10}; // parking slot1 infrared sensor connected with pin number 4 of arduino

int in    =A0; // used analog pin as digital out
int out   =A1;
byte val[4];
int count=0; 
int valin=0;
int valout=0;
int pos = 0; 
int cnt[3];
String sensor1; 
String sensor2; 
String sensor3; 
String sensor4; 
 
void pslot1(); 
void pslot2();
void pslot3(); 
void pslot4(); 
void gate_enter();
void gate_out();
   
String cdata =""; // complete data, consisting of sensors values


//************************************************************************************ void setup
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
pinMode(parking_slot[0], INPUT); 
pinMode(parking_slot[1], INPUT);
pinMode(parking_slot[2], INPUT); 
pinMode(parking_slot[3], INPUT);
pinMode(in, INPUT);
pinMode(out, INPUT);

myservo.attach(6);  

lcd.begin(16, 2);
lcd.clear();
  
myservo.write(0);
  
  for (pos = 0; pos <= 90; pos += 1)// goes from 0 degrees to 45 degrees
    { 
    myservo.write(pos);              
    delay(30);                       
    }
  delay(1000);
  for (pos = 90; pos >= 0; pos -= 1) // goes from 45 degrees to 0 degrees
      { 
      myservo.write(pos);             
      delay(30);                       
     }

//lcd.clear();
//lcd.setCursor(0, 0);

}
//******************************************************************************************** void loop
void loop()
{
 
 //********************************************************call user defined function
 
  pslot1(); 
  pslot2();
  pslot3(); 
  pslot4();
//********************************************************        
  gate_enter();
  gate_out();
  
   cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3 +","+ sensor4 + ","; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(500); // 100 milli seconds
   cdata = ""; 

digitalWrite(parking_slot[0], HIGH); 
digitalWrite(parking_slot[1], HIGH); 
digitalWrite(parking_slot[2], HIGH); 
digitalWrite(parking_slot[3], HIGH);
 //******************************************************** Display & servo 

lcd.setCursor(0, 0);
lcd.print("  AIUB PARKING");
if(count<4){
lcd.setCursor(0, 1);
lcd.print("cnt:");
lcd.setCursor(4, 1);
lcd.print(count);  
lcd.print("   "); 
//******************************************************* Display Available parking 

lcd.setCursor(8, 1);
lcd.print("P-L:");
 lcd.setCursor(12, 1);
  int y=0;
  for( y=0;y<4;y++)
       { 
        if(val[y]==1)
             {lcd.print(y+1);
              cnt[y]=1;
             }            
      }
lcd.print("      "); 
}     
//******************************************************** Taking gate signal
//valin=digitalRead(in);
//valout=digitalRead(out);
//********************************************************     PARKING FULL   
if(count>=4)
  {count=4;
  myservo.write(0);
    delay(1000);
    myservo.detach();
      lcd.setCursor(0, 1);
      lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Parking full");}
 //******************************************************** Code for Exit
}
 
 
void pslot1()                             // parkng slot 1
{
  if( digitalRead(parking_slot[0]) == LOW) 
  {
  sensor1 = "255"; // parking 
  val[0]=0;
 delay(200); 
  } 
if( digitalRead(parking_slot[0]) == HIGH)
{ 
  sensor1 = "0";  
 val[0]=1;
 delay(200);  
}
 
}
 
void pslot2()                                // parking slot 2
{
  if( digitalRead(parking_slot[1]) == LOW) 
  {
  sensor2 = "255"; 
  val[1]=0;
  delay(200); 
  }
if( digitalRead(parking_slot[1]) == HIGH ) 
  {
  sensor2 = "0";  
 val[1]=1;
 delay(200);
  } 
}
 
 
void pslot3()                                // parking slot 3
{
  if( digitalRead(parking_slot[2]) == LOW) 
  {
  sensor3 = "255"; 
  val[2]=0;
  delay(200); 
  }
if( digitalRead(parking_slot[2]) == HIGH)  
  {
  sensor3 = "0";  
 val[2]=1;
 delay(200);
  } 
}
 
 
void pslot4()                                // parking  slot 4
  {
  if( digitalRead(parking_slot[3]) == LOW) 
  {
  sensor4 = "255"; 
  val[3]=0;
  delay(200); 
  }
 if( digitalRead(parking_slot[3]) == HIGH)  
  {
  sensor4 = "0";  
 val[3]=1;
 delay(200);
  } 
 }

void gate_enter()
 {
 //********************************************  Code for Enter
 if(digitalRead(in) ==LOW)
     { 
         myservo.attach(6);   
         for (pos = 0; pos <= 90; pos += 1) 
                 { myservo.write(pos);delay(30);}  
          count++; 
         delay(1000);      
       for (pos = 90; pos >= 0; pos -= 1) 
                { myservo.write(pos);delay(30);}        
     } 
 }

 void gate_out()
 {
   if(digitalRead(out) ==LOW)
   {
     myservo.attach(6);  
    for (pos = 0; pos <= 90; pos += 1) 
            { myservo.write(pos);
            delay(30);}
     count--;
   if(count<=0)
       {count=0;} 
   delay(1000);     
   for (pos = 90; pos >= 0; pos -= 1) 
        { myservo.write(pos);
            delay(30);}
   }
 }

 
  
