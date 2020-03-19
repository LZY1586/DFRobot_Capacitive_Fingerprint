#include <DFRobot_ID809.h>

DFRobot_ID809 sensor;

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  sensor.begin(Serial1);
  while(!Serial);
}

uint8_t ID,i;

void loop(){
  ID = sensor.getEmptyID();
  Serial.print("ID=");
  Serial.println(ID);
  for(i = 0; i< 3; i++){
    sensor.LEDCtrl(eLEDMode3, LEDBlue, 0);
    Serial.println("请按下手指");
    sensor.fingerprintCollection(10);
    sensor.LEDCtrl(eLEDMode3, LEDYellow, 0);
    Serial.println("请松开手指");
    while(sensor.detectFinger());
  }
  sensor.storeChar(ID);
  Serial.print("采集成功，ID=");
  Serial.println(ID);
}