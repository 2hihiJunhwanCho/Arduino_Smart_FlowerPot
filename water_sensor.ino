//스마트화분 작동 코드입니다.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
String str;
int oldmos=-1;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int Sensor_pin = A1; // Sensor pin = A1
int LED_R = 3; // RED LED = Pin No.3
int LED_G = 4; // GREEN LED = Pin No.4

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(LED_R,OUTPUT); 
  pinMode(LED_G,OUTPUT);
}

void loop()
{
  int soil_mos;
  
  soil_mos=1023-analogRead(0); 
  soil_mos=map(soil_mos, 0, 1023, 0, 100);
  if (oldmos!=soil_mos) {
    lcd.setCursor(0,0);
    lcd.print("Soil Moist :");
    lcd.print(soil_mos);
    lcd.print("%");
  }
  
  Serial.println(analogRead(Sensor_pin));
  delay(100); // s = 0.1

  if(analogRead(Sensor_pin) > 400){
    lcd.clear();
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,LOW);    
  }
  else{
    lcd.clear();
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G,HIGH);
  }
}
