/*!
 * @file getDeviceInformation.ino
 * @brief 获取指纹模块信息
 * @n 实验现象：串口打印出模块的ID、安全等级、波特率等信息
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

DFRobot_ID809 finger;

void setup(){
  /*初始化打印串口*/
  Serial.begin(9600);
  /*初始化Serial1*/
  Serial1.begin(115200);
  /*将Serial1作为指纹模块的通讯串口*/
  finger.begin(Serial1);
  /*等待Serial打开*/
  while(!Serial);
  /*测试设备与主控是否能正常通讯*/
  while(!finger.testConnection()){
    Serial.println("与设备通讯失败，请检查接线");
    delay(1000);
  }
}

uint8_t ID,i,ret;

void loop(){
  //设置模块ID号为1
  //setDeviceID(1);
  Serial.print("模块ID为:");
  //读取模块ID
  Serial.println(finger.getDeviceID());
  
  //设置模块安全等级3
  //setSecurityLevel(3);
  Serial.print("模块安全等级为:");
  //读取模块安全等级
  Serial.println(finger.getSecurityLevel());
  
  //设置模块波特率115200
  //setBaudrate(e115200bps);
  Serial.print("模块波特率为:");
  //读取模块波特率
  Serial.println(finger.getBaudrate());
  
  //开启自学功能
  //setAutoLearn(1);
  Serial.print("模块自学功能:");
  //读取模块自学功能状态
  Serial.println(finger.getAutoLearn());
  
  //设置模块序列号
  //setModuleSN("DFRobot");
  Serial.print("模块序列号为:");
  //读取模块序列号
  Serial.println(finger.getModuleSN());
  
  Serial.print("模块内部已注册指纹数量:");
  //获取注册用户数量
  Serial.println(finger.getEnrollCount());
  //获取用户列表
  //API待写
  
  Serial.print("指纹损坏数量:");
  //得到指纹损坏数量
  Serial.println(finger.getBrokenQuantity());
  //得到第一个损坏指纹ID
  //finger.getBrokenID();

  delay(1000);
}