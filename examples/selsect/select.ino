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
  sensor.LEDCtrl(eLEDMode3, LEDBlue, 0);
  Serial.println("请按下手指");
  sensor.fingerprintCollection(10);
  sensor.LEDCtrl(eLEDMode3, LEDYellow, 0);
  Serial.println("请松开手指");
  while(sensor.detectFinger());
  ID = sensor.search()
  if(ID){
	  Serial.println("匹配未成功");
  }else{
	  Serial.print("匹配成功,ID=");
	  Serial.println(ID);
  }
}