#include <DFRobot_Capacitive_Fingerprint.h>

DFRobot_CapacitiveFingerprint sensor;

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  sensor.begin(Serial1);
  while(!Serial);
}


void loop(){
  Serial.println(sensor.testConnection());
  sensor.getDeviceInfo();
  delay(1000);
}