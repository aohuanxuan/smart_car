
#ifndef SEND_H_
#define SEND_H_


void SendImageData(unsigned char * ImageData); //发送图像
void SendHex(unsigned char hex);               //发送16进制数
void SendMessage(uint8_t message);             //发送信息


#endif /* #ifndef SEND_H_ */