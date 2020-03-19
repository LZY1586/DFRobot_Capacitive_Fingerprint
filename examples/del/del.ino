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