//스마트화분 작동 코드입니다.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTPIN 6 // 디지털 5번핀 매핑!!
#define DHTTYPE DHT22 // DHT 11센서 !!
DHT dht(DHTPIN, DHTTYPE);
String str;
int oldmos=-1;
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BTSerial(2,3);

int Sensor_pin = A0   ; // Sensor pin = A0
int LED_R = 5; // RED LED = Pin No.3
int LED_G = 4; // GREEN LED = Pin No.4



void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();
  
  lcd.setCursor(3,1);
  lcd.write(0);

  pinMode(LED_R,OUTPUT); 
  pinMode(LED_G,OUTPUT);
}

void loop()
{
  int btn = BTSerial.read();
  int tem = dht.readTemperature();
  int hum = dht.readHumidity();
  int soil_mos;
  
  soil_mos=1023-analogRead(0); 
  soil_mos=map(soil_mos, 0, 1023, 0, 100);
  if (oldmos!=soil_mos) {
    lcd.setCursor(2,2);
    lcd.print("Soil Moist :");
    lcd.print(soil_mos);
    lcd.print("%");
  }
  
  Serial.println(analogRead(Sensor_pin));
  delay(100); // s = 0.1

  if(analogRead(Sensor_pin) > 700){
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G,HIGH);    
  } // 35%일대 초록불 점등
  else{
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,LOW);
  }
  if (btn = '0') {
    BTSerial.print("온도 : ");
    BTSerial.print(tem);
    BTSerial.println("℃");
    BTSerial.print("습도 : ");
    BTSerial.println(hum);
    delay(1000);
  }

  
  
  if (btn = '5') {
    BTSerial.print("토양수분 : ");
    BTSerial.print(soil_mos);
    BTSerial.println("%");
  }
}
