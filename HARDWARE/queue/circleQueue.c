#include "stdlib.h"
#include "circleQueue.h"  
 
 

///*************************
//@fun :初始化队列
//@param：队列数据结构指针
//@return：1->success; 0->fail

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
//@fun :判断队列是否非空
//@param：队列数据结构指针
//@return：1->empty ; 0->unempty

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
//@fun :判断队列是否满
//@param：队列数据结构指针
//@return：1->full ; 0->unfull

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
//@fun :队尾压入数据
//@param：队列数据结构指针，待压入数据
//@return：1->success ; 0->fail

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
//@fun :弹出队首数据
//@param：队列数据结构指针，储存弹出数据指针
//@return：1->success ; 0->fail

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

//@fun :仅读取队首数据
//@param：队列数据结构指针，储存读取到的数据指针
//@return：1->success ; 0->fail

//**************************/
//char GetHeadElement(CircleQueue *pCQ, u8 *pData)  
//{  
//    if (IsQueueEmpty(pCQ))  
//        return 0;  
//  
//    *pData = pCQ->data[(pCQ->front + 1) % QUEUESIZE];  
//    return 1;  
//}


