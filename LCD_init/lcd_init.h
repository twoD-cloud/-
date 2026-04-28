#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "board.h"

#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define background_color 0x001F

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128

#endif



//-----------------LCD�˿ڶ���---------------- 

//-----------------LCD端口定义----------------

#define LCD_RES_Clr()  DL_GPIO_clearPins(LCD_PORT,LCD_RES_PIN)//RES
#define LCD_RES_Set()  DL_GPIO_setPins(LCD_PORT,LCD_RES_PIN)

#define LCD_DC_Clr()   DL_GPIO_clearPins(LCD_PORT,LCD_DC_PIN)//DC
#define LCD_DC_Set()   DL_GPIO_setPins(LCD_PORT,LCD_DC_PIN)

#define LCD_CS_Clr()   DL_GPIO_clearPins(LCD_PORT,LCD_CS_PIN)//CS
#define LCD_CS_Set()   DL_GPIO_setPins(LCD_PORT,LCD_CS_PIN)

#define LCD_BLK_Clr()  DL_GPIO_clearPins(LCD_PORT,LCD_BLK_PIN)//BLK
#define LCD_BLK_Set()  DL_GPIO_setPins(LCD_PORT,LCD_BLK_PIN)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




