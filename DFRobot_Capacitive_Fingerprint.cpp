#include <DFRobot_Capacitive_Fingerprint.h>
#include <Arduino.h>
#include <string.h>
#include <stdio.h>
Stream *dbg=NULL;
uint16_t _PacketSize = 0;

DFRobot_CapacitiveFingerprint::DFRobot_CapacitiveFingerprint()
  :s(NULL){
		
}

DFRobot_CapacitiveFingerprint::~DFRobot_CapacitiveFingerprint(){
		
}

bool DFRobot_CapacitiveFingerprint::begin(Stream &s_){
    s = &s_;
    if(s == NULL){
        return false;
    }
    return true;
}

uint8_t DFRobot_CapacitiveFingerprint::testConnection(){
	pCmdPacketHeader_t header = cmdPacked(CMD_TEST_CONNECTION, NULL, 0);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::setDeviceID(uint8_t deviceID){
	uint8_t data[5] = {0};
	_did = deviceID;
	data[1] = deviceID;
	pCmdPacketHeader_t header = cmdPacked(CMD_SET_PARAM, data, 5);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::setSecurityLevel(uint8_t securityLevel){
	uint8_t data[5] = {0};
	data[0] = 1;
	data[1] = securityLevel;
	pCmdPacketHeader_t header = cmdPacked(CMD_SET_PARAM, data, 5);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::setDuplicationCheck(uint8_t duplicationCheck){
	uint8_t data[5] = {0};
	data[0] = 2;
	data[1] = duplicationCheck;
	pCmdPacketHeader_t header = cmdPacked(CMD_SET_PARAM, data, 5);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::setBaudrate(eDEVICE_BAUDRATE_t baudrate){
	uint8_t data[5] = {0};
	data[0] = 3;
	data[1] = baudrate;
	pCmdPacketHeader_t header = cmdPacked(CMD_SET_PARAM, data, 5);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::setAutoLearn(uint8_t autoLearn){
	uint8_t data[5] = {0};
	data[0] = 4;
	data[1] = autoLearn;
	pCmdPacketHeader_t header = cmdPacked(CMD_SET_PARAM, data, 5);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::readDeviceID(){
	uint8_t data[1];
	data[0] = 0;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_PARAM, data, 1);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::readSecurityLevel(){
	uint8_t data[1];
	data[0] = 0;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_PARAM, data, 1);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::readDuplicationCheck(){
	uint8_t data[1];
	data[0] = 0;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_PARAM, data, 1);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::readBaudrate(){
	uint8_t data[1];
	data[0] = 0;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_PARAM, data, 1);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::readAutoLearn(){
	uint8_t data[1];
	data[0] = 0;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_PARAM, data, 1);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::getDeviceInfo(){
	pCmdPacketHeader_t header = cmdPacked(CMD_DEVICE_INFO, NULL, 0);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	uint8_t data[buf[0]];
	ret = responseDataPayload(data);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::LEDCtrl(eLED_MODE_t mode,eLED_COLOR_t color,uint8_t blinkCount){
	uint8_t data[4] = {0};
	data[0] = mode;
	data[2] = data[1] = color;
	data[3] = blinkCount;
	pCmdPacketHeader_t header = cmdPacked(CMD_SLED_CTRL, data, 4);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::detectFinger(){
	pCmdPacketHeader_t header = cmdPacked(CMD_FINGER_DETECT, NULL, 0);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::getEmptyID(){
	uint8_t data[4] = {0};
	data[0] = 1;
	data[2] = 80;     //该模块最多80个指纹，默认全部范围
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_EMPTY_ID, data, 4);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::getStatusID(uint8_t ID){
	uint8_t data[2] = {0};
	data[0] = ID;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_STATUS, data, 2);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

uint8_t DFRobot_CapacitiveFingerprint::getEnrollCount(){
	uint8_t data[4] = {0};
	data[0] = 1;
	data[2] = 80;
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_ENROLL_COUNT, data, 4);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return buf[0];
}

void DFRobot_CapacitiveFingerprint::setCollectNumber(uint8_t number){
	_number = number;
	if(number > 3||number <1){
		_number = 3;
		//LDBG("设置采集次数不在1-3之间，已自动设置为3次");
	}
}

uint8_t DFRobot_CapacitiveFingerprint::generate(){
	uint8_t ret;
	while(!detectFinger()){
		delay(20);
	}
	ret = getImage();
	//Serial.println(ret);
	if(ret == 1){
		uint8_t data[2] = {0};
		data[0] = _new;
		_new++;
		pCmdPacketHeader_t header = cmdPacked(CMD_GENERATE, data, 2);
		sendPacket(header);
		ret = responsePayload(buf);
	}
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::storeChar(uint8_t ID){
	uint8_t data[4] = {0};
	uint8_t ret = merge();
	_new = 0;
	data[0] = ID;
	pCmdPacketHeader_t header = cmdPacked(CMD_STORE_CHAR, data, 4);
	sendPacket(header);
	ret = responsePayload(buf);
	if(ret == 0x18){
		//LDBG("该指纹已注册");
		return buf[0];
	}
	//LDBG("ret=");LDBG(ret);
	return ret;
	
}

uint8_t DFRobot_CapacitiveFingerprint::delChar(uint8_t ID){
	uint8_t data[4] = {0};
	if(ID == DELALL){
		data[0] = 1;
		data[2] = 80;
	}else{
		data[0] = data[2] = ID;
	}
	pCmdPacketHeader_t header = cmdPacked(CMD_DEL_CHAR, data, 4);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::search(){
	uint8_t data[6] = {0};
	data[2] = 1;
	data[4] = 80;
	pCmdPacketHeader_t header = cmdPacked(CMD_SEARCH, data, 6);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	if(ret){           //如果对比成功返回ID
		ret = buf[0];
	}
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::verify(uint8_t ID){
	uint8_t data[4] = {0};
	data[0] = ID;
	pCmdPacketHeader_t header = cmdPacked(CMD_VERIFY, data, 4);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::enterStandbyState(){
	pCmdPacketHeader_t header = cmdPacked(CMD_ENTER_STANDBY_STATE, NULL, 0);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}
/**********************************************************************/


uint8_t DFRobot_CapacitiveFingerprint::getImage(){
	pCmdPacketHeader_t header = cmdPacked(CMD_GET_IMAGE, NULL, 0);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::merge(){
	uint8_t data[3] = {0};
	data[2] = _number;
	pCmdPacketHeader_t header = cmdPacked(CMD_MERGE, data, 3);
	sendPacket(header);
	uint8_t ret = responsePayload(buf);
	//LDBG("ret=");LDBG(ret);
	return ret;
}

pCmdPacketHeader_t DFRobot_CapacitiveFingerprint::cmdPacked(uint16_t cmd, const char *pay_, uint16_t len){
	pCmdPacketHeader_t header;     //????
	uint16_t cks=0;
	free(header);
	if((header = (pCmdPacketHeader_t)malloc(sizeof(sCmdPacketHeader_t))) == NULL){
    //LDBG("\r\n");
		return NULL;
    }
	header->PREFIX = CMD_PREFIX_CODE;
	header->SID = _sid;
	header->DID = _did;
	header->CMD = cmd;
	header->LEN = len;
	for(int i=0;i<16;i++){
		header->payload[i] = 0;
	}
	//memset(header->payload,0,16);
	if(len){
		memcpy((const char *)header->payload, pay_, len);
	}
	header->CKS = getCmdPacketCKS(header);
	_PacketSize = sizeof(sCmdPacketHeader_t);
	return header;
}

pCmdDataPacketHeader_t DFRobot_CapacitiveFingerprint::cmdDataPacked(uint16_t cmd, const char *pay_, uint16_t len){
	pCmdDataPacketHeader_t header;
	uint16_t cks=0;
	free(header);
	if((header = (pCmdDataPacketHeader_t)malloc(sizeof(sCmdDataPacketHeader_t))+len) == NULL){
    //LDBG("\r\n");
		return NULL;
    }
	header->PREFIX = CMD_DATA_PREFIX_CODE;
	header->SID = _sid;
	header->DID = _did;
	header->CMD = cmd;
	header->LEN = len;
	memcpy((const char *)header->payload, pay_, len);
	
	header->CKS = getCmdDataPacketCKS(header);
	_PacketSize = sizeof(sCmdDataPacketHeader_t);
	return header;
}

void DFRobot_CapacitiveFingerprint::sendPacket(pCmdPacketHeader_t header){
	//LDBG("SID=");LDBG(header->SID, HEX);
	//LDBG("DID=");LDBG(header->DID, HEX);
	//LDBG("CMD=");LDBG(header->CMD, HEX);
	//LDBG("LEN=");LDBG(header->LEN, HEX);
	//LDBG("DATA=");LDBG(header->payload[0], HEX);
	//LDBG("CKS=");LDBG(header->CKS, HEX);
	//LDBG("Size=");LDBG(_PacketSize);
	s->write((uint8_t *)header,_PacketSize);
	free(header);
	
}

uint8_t DFRobot_CapacitiveFingerprint::responsePayload(void* buf){
	sRcmPacketHeader_t header;
	size_t dataLen;
	uint8_t ch;
	uint8_t ret;
	if(readPacketPrefix(&header) < 0){
		//LDBG("--readPacketPrefix error---");
		return 0;
	}
	ret = !(header.RET>>8);
	if(header.RET == 1){
		//LDBG("--Module failed to execute---");
	}
	pRcmPacketHeader_t packet = (pRcmPacketHeader_t)malloc(sizeof(sRcmPacketHeader_t));
	if(packet == NULL){
        //LDBG("");
		while(1);
	}
	memcpy(packet, &header, 10);
  //LDBG("cmd=");LDBG(packet->cmd);
  //LDBG("length=");LDBG(packet->length);
  //LDBG("length=");LDBG(strlen(packet->payload));
  //LDBG("payload=");LDBG((const char *)packet->payload);
    dataLen = readN(packet->payload, 14);
	readN(&packet->CKS,2);
	
	//LDBG("Rcs=");LDBG(packet->CKS);
    if(dataLen != 14){
		//LDBG("--recvRspPacket length error---");
	}else if(getRcmPacketCKS(packet) != packet->CKS){
		//LDBG("--recvRspPacket cs error---");
	}else{
		//LDBG("--recvRspPacket OK---");
		memcpy(buf, packet->payload, 14);
	}
	free(packet);
	packet = NULL;
	return ret;
}

int16_t DFRobot_CapacitiveFingerprint::readPacketPrefix( pRcmPacketHeader_t header ){
	int16_t ret = 0;
	uint8_t ch;
	typedef enum{
		RECV_HEADER_INIT,
		RECV_HEADER_AA,
		RECV_HEADER_OK
	}eRecvHeaderState;
	eRecvHeaderState state = RECV_HEADER_INIT;
	while(state != RECV_HEADER_OK){
		if(readN(&ch, 1) != 1){
			ret = -1;
			break;
		}
		
		if((ch == 0xAA) && (state == RECV_HEADER_INIT)){
			state = RECV_HEADER_AA;
			continue;
		}else if((ch == 0x55) && (state == RECV_HEADER_AA)){
			state = RECV_HEADER_OK;
			continue;
		}else{
			//LDBG(ch,HEX);
			state = RECV_HEADER_INIT;
			if(ch == 0xAA){
				state = RECV_HEADER_AA;
			}
		}
	}
	header->PREFIX = RCM_PREFIX_CODE;
	readN(&header->SID, 1);
    readN(&header->DID, 1);
    readN(&header->RCM, 2);
    readN(&header->LEN, 2);
	readN(&header->RET, 2);
	return ret;
}
///可与上面合并   
int16_t DFRobot_CapacitiveFingerprint::readDataPacketPrefix( pRcmDataPacketHeader_t header ){
	int16_t ret = 0;
	uint8_t ch;
	typedef enum{
		RECV_HEADER_INIT,
		RECV_HEADER_A5,
		RECV_HEADER_OK
	}eRecvHeaderState;
	eRecvHeaderState state = RECV_HEADER_INIT;
	while(state != RECV_HEADER_OK){
		if(readN(&ch, 1) != 1){
			ret = -1;
			break;
		}
		
		if((ch == 0xA5) && (state == RECV_HEADER_INIT)){
			state = RECV_HEADER_A5;
			continue;
		}else if((ch == 0x5A) && (state == RECV_HEADER_A5)){
			state = RECV_HEADER_OK;
			continue;
		}else{
			//LDBG(ch,HEX);
			state = RECV_HEADER_INIT;
			if(ch == 0xA5){
				state = RECV_HEADER_A5;
			}
		}
	}
	header->PREFIX = RCM_DATA_PREFIX_CODE;
	readN(&header->SID, 1);
    readN(&header->DID, 1);
    readN(&header->RCM, 2);
    readN(&header->LEN, 2);
	readN(&header->RET, 2);
	return ret;
}

uint8_t DFRobot_CapacitiveFingerprint::responseDataPayload(void* buf){
	sRcmDataPacketHeader_t header;
	size_t dataLen;
	uint8_t ch;
	uint8_t ret;
	if(readDataPacketPrefix(&header) < 0){
		//LDBG("--readPacketPrefix error---");
		return 0;
	}
	ret = !(header.RET>>8);
	if(header.RET == 1){
		//LDBG("--Module failed to execute---");
	}
	pRcmDataPacketHeader_t packet = (pRcmDataPacketHeader_t)malloc(sizeof(sRcmDataPacketHeader_t));
	if(packet == NULL){
        //LDBG("");
		while(1);
	}
	memcpy(packet, &header, 10);
  //LDBG("cmd=");LDBG(packet->cmd);
  //LDBG("length=");LDBG(packet->length);
  //LDBG("length=");LDBG(strlen(packet->payload));
  //LDBG("payload=");LDBG((const char *)packet->payload);
    dataLen = readN(packet->payload, packet->LEN);
	readN(&packet->CKS,2);
	
	//LDBG("Rcs=");LDBG(packet->CKS);
    if(dataLen != packet->LEN){
		//LDBG("--recvRspPacket length error---");
	}else if(getRcmDataPacketCKS(packet) != packet->CKS){
		//LDBG("--recvRspPacket cs error---");
	}else{
		//LDBG("--recvRspPacket OK---");
		memcpy(buf, packet->payload, packet->LEN);
	}
	free(packet);
	packet = NULL;
	return ret;
}

size_t DFRobot_CapacitiveFingerprint::readN(void* buf_, size_t len){
    size_t offset = 0,left = len;
	uint8_t *buf = (uint8_t*)buf_;
	long long curr = millis();
	while(left){
		if(s->available()){
			buf[offset++] = s->read();
		//	LDBG(buf[offset-1], HEX);
		    left--;
		}
		if(millis() - curr > 5000){
			//LDBG("----------!!!!!!!!!recv timeout----------");
			break;
		}
	}
	return offset;
}

uint16_t DFRobot_CapacitiveFingerprint::getCmdPacketCKS(pCmdPacketHeader_t  packet){
	uint16_t cks = 0;
	cks += packet->PREFIX&0xFF;
	cks += packet->PREFIX>>8;
	cks += packet->SID;
	cks += packet->DID;
	cks += packet->CMD&0xFF;
	cks += packet->CMD>>8;
	cks += packet->LEN&0xFF;
	cks += packet->LEN>>8;
	if(packet->LEN > 0){
		uint8_t *p = packet->payload;
		for(uint8_t i = 0; i < packet->LEN; i++){
			cks += p[i];
		}
	}
	return cks;
}

uint16_t DFRobot_CapacitiveFingerprint::getRcmPacketCKS(pRcmPacketHeader_t packet){
	uint16_t cks = 0;
	cks += packet->PREFIX&0xFF;
	cks += packet->PREFIX>>8;
	cks += packet->SID;
	cks += packet->DID;
	cks += packet->RCM&0xFF;
	cks += packet->RCM>>8;
	cks += packet->LEN&0xFF;
	cks += packet->LEN>>8;
	if(packet->LEN > 0){
		uint8_t *p = packet->payload;
		for(uint8_t i = 0; i < packet->LEN; i++){
			cks += p[i];
		}
	}
	return cks;
}

uint16_t DFRobot_CapacitiveFingerprint::getCmdDataPacketCKS(pCmdDataPacketHeader_t  packet){
	uint16_t cks = 0;
	cks += packet->PREFIX&0xFF;
	cks += packet->PREFIX>>8;
	cks += packet->SID;
	cks += packet->DID;
	cks += packet->CMD&0xFF;
	cks += packet->CMD>>8;
	cks += packet->LEN&0xFF;
	cks += packet->LEN>>8;
	if(packet->LEN > 0){
		uint8_t *p = packet->payload;
		for(uint16_t i = 0; i < packet->LEN; i++){
			cks += p[i];
		}
	}
	return cks&0xFFFF;
}

uint16_t DFRobot_CapacitiveFingerprint::getRcmDataPacketCKS(pRcmDataPacketHeader_t packet){
	uint16_t cks = 0;
	cks += packet->PREFIX&0xFF;
	cks += packet->PREFIX>>8;
	cks += packet->SID;
	cks += packet->DID;
	cks += packet->RCM&0xFF;
	cks += packet->RCM>>8;
	cks += packet->LEN&0xFF;
	cks += packet->LEN>>8;
	if(packet->LEN > 0){
		uint8_t *p = packet->payload;
		for(uint16_t i = 0; i < packet->LEN; i++){
			cks += p[i];
		}
	}
	return cks&0xFFFF;
}


