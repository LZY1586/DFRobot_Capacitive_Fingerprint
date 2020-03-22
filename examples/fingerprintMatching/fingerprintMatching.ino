/*!
 * @file fingerprintMatching.ino.ino
 * @brief 采集指纹并与指纹库中指纹做对比
 * @n 实验现象：采集指纹图像并与指纹库中的指纹最对比，
                对比成功亮绿色灯并打印ID号，对比失败返回0
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](Eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-03-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_SHT3x
*/
#include <DFRobot_ID809.h>

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

uint8_t ret;

void loop(){
  /*将指纹灯环设置为蓝色快闪*/
  finger.LEDCtrl(finger.eFastBlink, finger.LEDBlue, /*flashing number=*/0);
  Serial.println("请按下手指");
  /*采集指纹图像，超过10S没按下手指则采集超时*/
  if((ret = finger.fingerprintCollection(/*timeout=*/10)) != 0){
    //打印ret对应的错误码
    Serial.println("采集失败");
  }else{
    Serial.println("采集成功");
    /*将指纹灯环设置为黄色快闪3次*/
    finger.LEDCtrl(finger.eFastBlink, finger.LEDYellow, /*flashing number=*/3);
  }
  Serial.println("请松开手指");
  /*等待手指松开*/
  while(finger.detectFinger());
  
  /*将采集到的指纹与指纹库中的所有指纹对比，成功返回指纹编号，失败返回0*/
  ret = finger.search();
  //ret = finger.verify(1);  //将采集到的指纹与指纹库中的1号指纹对比
  if(ret){
	  /*将指纹灯环设置为红色常亮*/
	  finger.LEDCtrl(finger.eKeepsOn, finger.LEDRed, /*flashing number=*/0);
	  Serial.println("匹配失败");
  }else{
	  /*将指纹灯环设置为绿色常亮*/
	  finger.LEDCtrl(finger.eKeepsOn, finger.LEDGreen, /*flashing number=*/0);
	  Serial.print("匹配成功,ID=");
	  Serial.println(ID);
  }
  delay(1000);
}