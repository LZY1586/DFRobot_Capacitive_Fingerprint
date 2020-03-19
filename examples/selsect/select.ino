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
  /*初始化打印串口*/
  Serial.begin(9600);
  /*初始化Serial1*/
  Serial1.begin(115200);
  /*将Serial1作为指纹模块的通讯串口*/
  sensor.begin(Serial1);
  /*等待Serial打开*/
  while(!Serial);
}

uint8_t ret;

void loop(){
  /*将指纹灯环设置为蓝色快闪*/
  sensor.LEDCtrl(eLEDMode2, LEDBlue, 0);
  Serial.println("请按下手指");
  /*采集指纹图像，超过10S没按下手指则采集超时*/
  if((ret = sensor.fingerprintCollection(10)) != 0){
    //打印ret对应的错误码
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
  
  //将采集到的指纹与指纹库中的所有指纹对比
  ret = sensor.search();
  //ret = sensor.verify(1);  //将采集到的指纹与指纹库中的1号指纹对比
  if(ret){
	  Serial.println("匹配失败");
  }else{
	  Serial.print("匹配成功,ID=");
	  Serial.println(ID);
  }
}