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
include <DFRobot_ID809.h>

#define DELID 5

DFRobot_ID809 sensor;

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  sensor.begin(Serial1);
  while(!Serial);
  if(sensor.getStatusID(DELID)){
	Serial.println("ID已注册");
	sensor.delChar(DELID);
	//sensor.delChar(DELALL);  //删除所有指纹
	Serial.println("ID已删除");
  }else{
	  Serial.println("ID未注册");
  }
}

void loop(){
  if(sensor.getStatusID(DELID)){
	Serial.println("ID已注册");
  }else{
	  Serial.println("ID未注册");
  }
  delay(1000);
}