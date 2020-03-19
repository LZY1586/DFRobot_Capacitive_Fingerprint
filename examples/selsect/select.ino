/*!
 * @file add.ino
 * @brief 采集指纹并保存
 * @n 实验现象：自动获取空白ID，然后采集三次指纹，最后保存到获取到的空白ID中
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_SHT3x
*/
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