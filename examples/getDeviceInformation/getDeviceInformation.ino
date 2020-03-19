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

#define COLLECT_NUMBER 3  //指纹采样次数，可设置1-3

DFRobot_ID809 sensor;

void setup(){
  /*初始化打印串口*/
  Serial.begin(9600);
  /*初始化Serial1*/
  Serial1.begin(115200);
  /*将Serial1作为指纹模块的通讯串口*/
  sensor.begin(Serial1);
  /*等待Serial打开*/
  while(!Serial);
}

uint8_t ID,i,ret;

void loop(){
  /*获取一个未注册编号，用来保存指纹*/
  if((ret = sensor.testConnection()) == 0){
	  Serial.println("连接正常");
  }
  //设置模块ID号为1
  //setDeviceID(1);
  Serial.print("模块ID为:");
  //读取模块ID
  Serial.println(sensor.getDeviceID());
  //设置模块安全等级3
  //setSecurityLevel(3);
  Serial.print("模块安全等级为:");
  //读取模块安全等级
  Serial.println(sensor.getSecurityLevel());
  //开启指纹重复检查
  //setDuplicationCheck(1);
  Serial.print("模块指纹重复检测状态:");
  //读取模块指纹重复检查状态
  Serial.println(sensor.getDuplicationCheck());
  //设置模块波特率115200
  //setBaudrate(e115200bps);
  Serial.print("模块波特率为:");
  //读取模块波特率
  Serial.println(sensor.getBaudrate());
  //开启自学功能
  //setAutoLearn(1);
  Serial.print("模块自学功能:");
  //读取模块自学功能状态
  Serial.println(sensor.getAutoLearn());
  
  //设置模块序列号
  //setModuleSN("DFRobot");
  Serial.print("模块序列号为:");
  //读取模块序列号
  Serial.println(sensor.getModuleSN());
  
  Serial.print("模块内部已注册指纹数量:");
  //获取注册用户数量
  Serial.println(sensor.getEnrollCount());

  delay(1000);
}