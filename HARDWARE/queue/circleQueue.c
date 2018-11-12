#include "stdlib.h"
#include "circleQueue.h"  
 
 

///*************************
//@fun :��ʼ������
//@param���������ݽṹָ��
//@return��1->success; 0->fail

//**************************/
//char InitCircleQueue(CircleQueue *pCQ)  
//{  
//    //pCQ = (CircleQueue *)malloc(sizeof(CircleQueue));  
//    if (pCQ == NULL)  
//        return 0;  

//    pCQ->front = 0;  
//    pCQ->tail = 0;  
//    return 1;  
//}  
//  

///*************************
//@fun :�ж϶����Ƿ�ǿ�
//@param���������ݽṹָ��
//@return��1->empty ; 0->unempty

//**************************/
//inline char IsQueueEmpty(CircleQueue *pCQ)  
//{  
//    if (pCQ->front == pCQ->tail)  
//        return 1;
//        
//    return 0;
//}  
// 

///*************************
//@fun :�ж϶����Ƿ���
//@param���������ݽṹָ��
//@return��1->full ; 0->unfull

//**************************/
//inline char IsQueueFull(CircleQueue *pCQ)  
//{  
//    if ((pCQ->tail + 1) % QUEUESIZE == pCQ->front)  
//        return 1;  
//    
//    return 0;  
//}  
// 
///*************************
//@fun :��βѹ������
//@param���������ݽṹָ�룬��ѹ������
//@return��1->success ; 0->fail

//**************************/
//inline char PushElement(CircleQueue *pCQ, u8 dData)  
//{  
//    if (IsQueueFull(pCQ))  
//        return 0;  
//  
//    pCQ->tail = (pCQ->tail + 1) % QUEUESIZE;  
//    pCQ->data[pCQ->tail] = dData;  
//    return 1;  
//}  
// 

///*************************
//@fun :������������
//@param���������ݽṹָ�룬���浯������ָ��
//@return��1->success ; 0->fail

//**************************/
//inline char PopElement(CircleQueue *pCQ, u8 *pData)  
//{  
//    if (IsQueueEmpty(pCQ))  
//        return 0;  
//  
//    pCQ->front = (pCQ->front + 1) % QUEUESIZE;  
//    *pData = pCQ->data[pCQ->front];  
//    return 1;  
//}  
//  

///*************************

//@fun :����ȡ��������
//@param���������ݽṹָ�룬�����ȡ��������ָ��
//@return��1->success ; 0->fail

//**************************/
//char GetHeadElement(CircleQueue *pCQ, u8 *pData)  
//{  
//    if (IsQueueEmpty(pCQ))  
//        return 0;  
//  
//    *pData = pCQ->data[(pCQ->front + 1) % QUEUESIZE];  
//    return 1;  
//}


