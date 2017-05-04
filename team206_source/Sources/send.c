/*********************************************************
                       send.c
                     串口传数据函数
********************************************************/



#include "includes.h"


void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    SCI0_SendChar1('*');
    SCI0_SendChar1('L');
    SCI0_SendChar1('D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    SCI0_SendChar1('#');
}

void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    SCI0_SendChar1(temp + '0');
  } else {
    SCI0_SendChar1(temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    SCI0_SendChar1(temp + '0');
  } else {
    SCI0_SendChar1(temp - 10 + 'A');
  }
}

void SendMessage(uint8_t message) 
{
  SCI0_SendChar1(message);  
}