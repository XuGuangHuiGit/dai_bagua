#ifndef __CIRCLEQUEUE__H
#define __CIRCLEQUEUE__H


#include "sys.h"



#define QUEUESIZE 100 //定义队列的大小

typedef struct  
{  
    u8 data[QUEUESIZE];  
    u16 front; //指向队头的索引，这个所指的空间不存放元素  
    u16 tail; //指向队尾的索引，存放最后一个元素  
} CircleQueue;  






char InitCircleQueue(CircleQueue *pdata);
char IsQueueEmpty(CircleQueue *pCQ);
char IsQueueFull(CircleQueue *pCQ);
char PushElement(CircleQueue *pCQ, u8 dData);
char PopElement(CircleQueue *pCQ, u8 *pData);
char GetHeadElement(CircleQueue *pCQ, u8 *pData);





#endif



