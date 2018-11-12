#ifndef __CIRCLEQUEUE__H
#define __CIRCLEQUEUE__H


#include "sys.h"



#define QUEUESIZE 100 //������еĴ�С

typedef struct  
{  
    u8 data[QUEUESIZE];  
    u16 front; //ָ���ͷ�������������ָ�Ŀռ䲻���Ԫ��  
    u16 tail; //ָ���β��������������һ��Ԫ��  
} CircleQueue;  






char InitCircleQueue(CircleQueue *pdata);
char IsQueueEmpty(CircleQueue *pCQ);
char IsQueueFull(CircleQueue *pCQ);
char PushElement(CircleQueue *pCQ, u8 dData);
char PopElement(CircleQueue *pCQ, u8 *pData);
char GetHeadElement(CircleQueue *pCQ, u8 *pData);





#endif



