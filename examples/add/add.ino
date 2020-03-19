/*!
 * @file add.ino
 * @brief 采集指纹并保存
 * @n 本实验需要Leonardo主控和ID809指纹模块
 * @n 实验现象：自动获取空白ID，然后采集三次指纹，
 * @n 采集时蓝色灯快闪，采集成功黄色灯快闪3次，
 * @n 最后保存到获取到的空白ID中，绿色灯亮1S然后熄灭
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

uint8_t ID,i;

void loop(){
  /*获取一个空白ID*/
  ID = sensor.getEmptyID();
  Serial.print("ID=");
  Serial.println(ID);
  /*指纹采样三次*/
  for(i = 0; i< COLLECT_NUMBER; i++){
    /*将指纹灯环设置为蓝色快闪*/
    sensor.LEDCtrl(eLEDMode2, LEDBlue, 0);
    Serial.println("请按下手指");
    /*采集指纹图像，超过10S没按下手指则采集超时*/
    if(sensor.fingerprintCollection(10) != 0){
      Serial.println("采集失败");
      i--;
    }else{
      Serial.println("采集成功");
      /*将指纹灯环设置为黄色快闪3次*/
      sensor.LEDCtrl(eLEDMode2, LEDYellow, 3);
    }
    Serial.println("请松开手指");
    /*等待手指松开*/
    while(sensor.detectFinger());
  }
  /*保存指纹*/
  sensor.storeChar(ID);
  Serial.print("保存成功，ID=");
  Serial.println(ID);
  /*将指纹灯环设置为绿色常亮*/
  sensor.LEDCtrl(eLEDMode3, LEDGreen, 0);
  delay(1000);
  /*关闭指纹灯环*/
  sensor.LEDCtrl(eLEDMode4, LEDBlue, 0);
  delay(1000);
}