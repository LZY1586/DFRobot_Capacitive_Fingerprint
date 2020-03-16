#include <DFRobot_Capacitive_Fingerprint.h>

DFRobot_CapacitiveFingerprint sensor;

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  sensor.begin(Serial1);
  //开启重复指纹检测
  sensor.setDuplicationCheck(1);
  //采集次数3次
  sensor.setCollectNumber(3);
  while(!Serial);
}

uint8_t ret,ID;
void loop(){
  ID = sensor.getEmptyID();
  for(uint8_t i = 0; i < 3; i++){
	  sensor.LEDCtrl(eLEDMode3, LEDBlue, 0);
	  Serial.print("正在采集第:");
	  Serial.print(i+1);
	  Serial.println("次指纹图像");
	  sensor.generate();
	  sensor.LEDCtrl(eLEDMode3, LEDYellow, 0);
	  while(sensor.detectFinger());
  }
  ret = sensor.storeChar(ID);
  if(ret != 1){
	  sensor.LEDCtrl(eLEDMode3, LEDRed, 0);
	  delay(1000);
	  Serial.print("该指纹已被注册，ID=");
	  Serial.println(ret);
  }else{
	  sensor.LEDCtrl(eLEDMode3, LEDGreen, 0);
	  delay(1000);
	  Serial.print("指纹注册成功，ID=");
	  Serial.println(ret);
  }
}