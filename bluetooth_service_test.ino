
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5,6);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);d

}

void loop() {
  if(mySerial.available()){
    Serial.write(mySerial.read());
  }

  if(Serial.available()){
  mySerial.write(Serial.read());
  }
}
