#include<SoftwareSerial.h>

SoftwareSerial esp(3,2);//rx,tx

int temp = A0; //temperature sensor
 int inhael = A1; //mq sensor
 int wet = A2; //2 pin 
int sensorValue0; 
int outputValue0;   
int sensorValue1; 
int outputValue1;   
int sensorValue2; 
int outputValue2;
int buttonState = 0; 
const int pir= 4;
int buzzer=5;
int signal1=6;
int signal2=7;
int fan=1;
int humidity;
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

void setup()
{
   pinMode(pir,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(signal1,OUTPUT);
  pinMode(signal2,OUTPUT);
   pinMode(fan,OUTPUT);
   pinMode(buzzer,OUTPUT);
  //pinMode(sensorValue0,INPUT);
 // pinMode(sensorValue1,INPUT);
  //pinMode(sensorValue2,INPUT);
 lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("HEALTH MONITORING");  
    delay(1000);
    lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("   IOT BASED      ");
 
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp.begin(115200);
  esp.println("AT+CWMODE=3");
  delay(1000);
  esp.println("AT+CWJAP=\"BAYTONE\",\"av30162000\"");
  //esp.println("AT+CWJAP=\"POCO PHONE\",\"pras1234\"");
  
}

void loop()
{
  digitalWrite(fan,LOW);
  digitalWrite(signal2,LOW);
 digitalWrite(signal1,LOW);
    lcd.clear();
  sensorValue0 = analogRead(temp);
  temp = map(sensorValue0, 0, 1023, 0, 180);
  lcd.setCursor(0,0);
  lcd.print("HEAT = ");
  lcd.print(temp);
  humidity= temp*1.1;
  delay(3000);

  sensorValue1 = analogRead(inhael);
  inhael = map(sensorValue1, 0, 1023, 0, 100);
  lcd.clear();
  lcd.print("AIR DENSITY=");
  delay(200);
  lcd.print(inhael);
   delay(3000);
   lcd.clear();
   
sensorValue2 = analogRead(wet);
  wet = map(sensorValue2, 0, 1023, 0,5);
  lcd.clear();
   lcd.print("WET HAPPND  ");
  digitalWrite(buzzer,HIGH);
  lcd.print(wet);

  //  lcd.print("C");
  delay(2000);
  digitalWrite(buzzer,LOW);

  esp.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
  delay(5000);
  esp.println("AT+CIPSEND=105");
  delay(2000);
 // esp.print("GET https://api.thingspeak.com/update?api_key=IFICBCVR5QLT812J&field1=0");//panimalar
  //GET https://api.thingspeak.com/update?api_key=IFICBCVR5QLT812J&field1=0
  esp.print("GET https://api.thingspeak.com/update?api_key=JTQSSQ5QR9FORLE0&field1=0");//bio
  esp.print(temp);//smoke
  esp.print("&field2=");
  esp.print(inhael);//pir
  esp.print("&field3=");
  esp.println(humidity);//temperature 
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("                    "); 
  lcd.setCursor(0,1);
  lcd.print("                    ");

if (temp>=100)

{
lcd.clear();
  lcd.print("HEAT HIGH");
  digitalWrite(fan,HIGH);
  digitalWrite(buzzer,HIGH);
  //Serial.print("L1");
  lcd.setCursor(0,1);
  delay(100);
 digitalWrite(signal1,HIGH);
  digitalWrite(signal2,LOW);
 delay(5000);
 digitalWrite(signal2,LOW);
 digitalWrite(signal1,LOW);
 delay(2000);
 digitalWrite(signal2,HIGH);
 //delay(100);
 digitalWrite(signal1,LOW);
  delay(5000);
 digitalWrite(signal2,LOW);
 digitalWrite(signal1,LOW);
 delay(2000);
 digitalWrite(fan,LOW);
  //digitalWrite(fan,HIGH);
  digitalWrite(buzzer,LOW);
}
else
{
  lcd.print("HEAT LOW");
  //Serial.print("L1");
  lcd.setCursor(0,1);
  delay(100);
 digitalWrite(signal1,LOW);
 digitalWrite(fan,LOW);
 delay(1000);
 digitalWrite(signal2,LOW);
}

}




