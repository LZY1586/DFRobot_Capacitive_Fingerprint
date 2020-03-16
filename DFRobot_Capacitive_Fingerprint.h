/*!
 * @file DFROBOT_Capacitive_Fingerprint.h
 * @brief 定义 DFROBOT_Capacitive_Fingerprint 类的基础结构
 * @n 这是一个电容指纹识别模块的库；
 * @n 其主要功能是采集手指图像、对比指纹、
 * @n 删除指纹等
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Eddard](eddard.liu@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-28
 * @https://github.com/DFRobot/DFRobot_IIC_Serial
 */

#ifndef _DFROBOT_CAPACITIVE_FINGERPRINT_H
#define _DFROBOT_CAPACITIVE_FINGERPRINT_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#include <stdint.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

//Open this macro to see the detailed running process of the program 
#ifdef ENABLE_DBG
#define LDBG(...) if(dbg) {dbg->print("["); dbg->print(__FUNCTION__); dbg->print("(): "); dbg->print(__LINE__); dbg->print(" ] "); dbg->println(__VA_ARGS__);}
#else
#define LDBG(...)
#endif

extern Stream *dbg;
  /*
   命令包的帧结构
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  CMD;
  uint16_t  LEN;
  uint8_t payload[16];
  uint16_t  CKS;
  
}__attribute__ ((packed)) sCmdPacketHeader_t, *pCmdPacketHeader_t;

  /*
   响应包的帧结构
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  RCM;
  uint16_t  LEN;
  uint16_t  RET;
  uint8_t   payload[14];
  uint16_t  CKS;
  
}__attribute__ ((packed)) sRcmPacketHeader_t, *pRcmPacketHeader_t;

  /*
   命令数据包的帧结构
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  CMD;
  uint16_t  LEN;
  uint16_t  CKS;
  uint8_t payload[0];
}__attribute__ ((packed)) sCmdDataPacketHeader_t, *pCmdDataPacketHeader_t;

  /*
   响应数据包的帧结构
  */
typedef struct{
  uint16_t  PREFIX;
  uint8_t   SID;
  uint8_t   DID;
  uint16_t  RCM;
  uint16_t  LEN;
  uint16_t  RET;
  uint16_t  CKS;
  uint8_t   payload[0];
}__attribute__ ((packed)) sRcmDataPacketHeader_t, *pRcmDataPacketHeader_t;


  typedef enum{
    eLEDMode1 = 1, //呼吸
    eLEDMode2, //快闪
    eLEDMode3, //常亮
    eLEDMode4, //常闭
    eLEDMode5, //渐开
    eLEDMode6, //渐关
    eLEDMode7  //慢闪
  }eLED_MODE_t;
  
  typedef enum{
    LEDGreen = 1, //绿色
    LEDRed,       //红色
    LEDYellow,    //黄色
    LEDBlue,      //蓝色
    LEDCyan,      //青色
	LEDMagenta,   //品红色
	LEDWhite      //白色
  }eLED_COLOR_t;
  
  typedef enum{
    e9600bps = 1,
    e19200bps,
    e38400bps,
    e57600bps,
    e115200bps,
	e230400bps,
	e460800bps,
	e921600bps
  }eDEVICE_BAUDRATE_t;
  


class DFRobot_CapacitiveFingerprint{
public: 

#define DELALL                   0xFF    //删除所有指纹

#define CMD_PREFIX_CODE          0xAA55  //命令包前缀代码
#define RCM_PREFIX_CODE          0x55AA  //响应包前缀代码
#define CMD_DATA_PREFIX_CODE          0x5AA5  //命令数据包前缀代码
#define RCM_DATA_PREFIX_CODE          0xA55A  //响应数据包前缀代码

#define CMD_TEST_CONNECTION      0X0001  //连接测试
#define CMD_SET_PARAM            0X0002  //设置参数
#define CMD_GET_PARAM            0X0003  //读取参数
	#define CMD_DEVICE_INFO          0X0004  //读取设备信息
	#define CMD_SET_MODULE_SN        0X0008  //设置模块序列号-------需求？
	#define CMD_GET_MODULE_SN        0X0009  //读取模块序列号-------需求？
#define CMD_ENTER_STANDBY_STATE  0X000C  //进入休眠状态
#define CMD_GET_IMAGE            0X0020  //采集指纹图像
#define CMD_FINGER_DETECT        0X0021  //检测手指
	#define CMD_UP_IMAGE_CODE        0X0022  //上传指纹图像到主机
	#define CMD_DOWN_IMAGE           0X0023  //下载指纹图像到模块
#define CMD_SLED_CTRL            0X0024  //控制采集器背光灯
#define CMD_STORE_CHAR           0X0040  //保存指纹模板数据到模块指纹库
	#define CMD_LOAD_CHAR            0X0041  //读取模块中的指纹并暂存在 RAMBUFFER 中
	#define CMD_UP_CHAR              0X0042  //将暂存在 RAMBUFFER 中的指纹模板上传到主机
	#define CMD_DOWN_CHAR            0X0043  //下载指纹模板数据到模块指定的 RAMBUFFER
#define CMD_DEL_CHAR             0X0044  //删除指定编号范围内的指纹
#define CMD_GET_EMPTY_ID         0X0045  //获取指定编号范围内可注册的首个编号
#define CMD_GET_STATUS           0X0046  //检查指定的编号是否已被注册
	#define CMD_GET_BROKEN_ID        0X0047  //检查指定范围内的指纹库是否有数据损坏
#define CMD_GET_ENROLL_COUNT     0X0048  //获取指定编号范围内已注册的指纹总数
	#define CMD_GET_ENROLLED_ID_LIST 0X0049  //获取已注册 ID 列表
#define CMD_GENERATE             0X0060  //从暂存在 IMAGEBUFFER 中的指纹图像产生模板
#define CMD_MERGE                0X0061  //合成指纹模板数据用于入库
	#define CMD_MATCH                0X0062  //指定2个RAMBUFFER 之间的模板做比对
#define CMD_SEARCH               0X0063  //指定编号范围的1:N识别
#define CMD_VERIFY               0X0064  //指定 RAMBUFFER 与指纹库中指定编号的模板比对


public:
  DFRobot_CapacitiveFingerprint();
  ~DFRobot_CapacitiveFingerprint();
  bool begin(Stream &s_);
  
  /**
   * @brief 测试模块是否正常连接
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t testConnection();
  
  /**
   * @brief 设置模块ID
   * @param ID号:1-255
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t setDeviceID(uint8_t DeviceID);
  
  /**
   * @brief 设置模块安全等级
   * @param 安全等级:1-5
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t setSecurityLevel(uint8_t SecurityLevel);
  
  /**
   * @brief 设置模块指纹重复检查(在保存指纹时，检查是否已被注册)
   * @param 1(ON) or 0(OFF)
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t setDuplicationCheck(uint8_t DuplicationCheck);
  
  /**
   * @brief 设置模块波特率
   * @param Baudrate:in typedef enum eDEVICE_BAUDRATE_t
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t setBaudrate(eDEVICE_BAUDRATE_t Baudrate);
  
  /**
   * @brief 设置模块自学功能(在对比指纹成功时，更新指纹)
   * @param 1(ON) or 0(OFF)
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t setAutoLearn(uint8_t AutoLearn);
  
  /**
   * @brief 读取模块ID
   * @return ID号:1-255
   */
  uint8_t readDeviceID();
  
  /**
   * @brief 读取模块安全等级
   * @return 安全等级:1-5
   */
  uint8_t readSecurityLevel();
  
  /**
   * @brief 读取模块指纹重复检查状态
   * @return 1(ON) or 0(OFF)
   */
  uint8_t readDuplicationCheck();
  
  /**
   * @brief 读取模块波特率
   * @return Baudrate:in typedef enum eDEVICE_BAUDRATE_t
   */
  uint8_t readBaudrate();
  
  /**
   * @brief 读取模块自学功能状态
   * @return 1(ON) or 0(OFF)
   */
  uint8_t readAutoLearn();
   
  /**
   * @brief 读取设备号
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t getDeviceInfo();
  
  /**
   * @brief 设置LED灯
   * @param mode:in typedef enum eLED_MODE_t
   * @param color:in typedef enum eLED_COLOR_t
   * @param 闪烁次数
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t LEDCtrl(eLED_MODE_t mode,eLED_COLOR_t color,uint8_t blinkCount);
  
  /**
   * @brief 检测是否有手指触碰
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t detectFinger();
  
  /**
   * @brief 获取可注册首个编号
   * @return 可注册ID号
   */
  uint8_t getEmptyID();
  
  /**
   * @brief 检查ID是否已被注册
   * @return 1(已注册) or 0(未注册)
   */
  uint8_t getStatusID(uint8_t ID);
  
  /**
   * @brief 获取注册用户数量
   * @return 注册用户数量
   */
  uint8_t getEnrollCount();
  
  /**
   * @brief 设置指纹采集次数
   * @param 采集次数:1-3
   */
   void setCollectNumber(uint8_t number);
  
  /**
   * @brief 获取指纹
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t generate();
  
  /**
   * @brief 保存指纹
   * @param 指纹ID
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t storeChar(uint8_t ID);
  
  /**
   * @brief 删除指纹
   * @param 指纹ID or DELALL(全部删除)
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t delChar(uint8_t ID);
  
  /**
   * @brief 将指纹与全部指纹匹配
   * @return 匹配成功的指纹ID or 0(defeated)
   */
  uint8_t search();

  /**
   * @brief 将指纹与指定指纹匹配
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t verify(uint8_t ID);
  
  /**
   * @brief 进入休眠状态
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t enterStandbyState();
  
  /*  
  //获取已注册用户ID
   getEnrolledIDList();
  */
  bool setDbgSerial(Stream &s_){dbg = &s_; return true;}
protected:
  /**
   * @brief 采集指纹图像
   * @return 1(succeed) or 0(defeated)
   */
  uint8_t getImage();
  
  //合成指纹
  uint8_t merge();
  
  pCmdPacketHeader_t cmdPacked(uint16_t cmd, const char *pay_, uint16_t len);
  pCmdDataPacketHeader_t cmdDataPacked(uint16_t cmd, const char *pay_, uint16_t len);
  
  void sendPacket(pCmdPacketHeader_t header);
  size_t readN(void* buf_, size_t len);
  
  int16_t readPacketPrefix( pRcmPacketHeader_t header );
  uint8_t responsePayload(void* buf);
  
  int16_t readDataPacketPrefix( pRcmDataPacketHeader_t header );
  uint8_t responseDataPayload(void* buf);
  
  uint16_t getCmdPacketCKS(pCmdPacketHeader_t  packet);
  uint16_t getRcmPacketCKS(pRcmPacketHeader_t packet);
  
  uint16_t getCmdDataPacketCKS(pCmdDataPacketHeader_t  packet);
  uint16_t getRcmDataPacketCKS(pRcmDataPacketHeader_t packet);
  
private:
  Stream *s;
  uint8_t buf[20];
  pCmdPacketHeader_t  sendHeader;
  pRcmPacketHeader_t  recHeader;
  
  pCmdDataPacketHeader_t sendDataHeader;
  pRcmDataPacketHeader_t recDataHeader;
  uint8_t _sid = 0;  
  uint8_t _did = 0;
  uint8_t _number = 3;            //指纹采集次数，默认三次
  uint8_t _new = 0;       //当前采集次数
};

#endif


