#include "usart_u.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cmd.h"

void Usart_init(USART_TypeDef* USARTx , u32 baud ,FunctionalState NewState){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    
	if(USARTx == USART1){
		return ;
	}else if (USARTx == USART2){
		return ;
	}else if (USARTx == USART3){
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //usart2--TX  
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//usart2--RX
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}else{
		return;
	}
	
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //提升USART时钟时使能还是失能，钟低电平活动
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;   //时钟第二个边缘进行数据捕获
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //指定SLCK引脚上时钟的极性
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;  //在SCLK引脚上输出最后发送的那个数据字的脉冲不从SCLK输出
	USART_ClockInit(USARTx, &USART_ClockInitStruct); 
	
	USART_Init(USARTx, &USART_InitStructure);
    USART_Cmd(USARTx, ENABLE);
    
	USART_ClearFlag(USARTx, USART_FLAG_TC);
	
	
    if(NewState){
        USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);       //使能接收中断
        if(USARTx == USART1){
            NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //设置串口1中断
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART1_Priority;         //抢占优先级 0
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART1_Priority;    //子优先级为0
        }else if (USARTx == USART2){
            NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //设置串口1中断
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART2_Priority;         //抢占优先级 0
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART2_Priority;    //子优先级为0
        }else if (USARTx == USART3){
            NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //设置串口1中断
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART3_Priority;         //抢占优先级 0
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART3_Priority;    //子优先级为0
        }else{
            return ;
        }
       
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能
        NVIC_Init(&NVIC_InitStructure);
        
    }
	
}
/**********************************************************
*   @fun：串口2中断服务函数，用于粗略读取GPS的UTC时间
*   
*
*********************************************************/
void USART2_IRQHandler(void){
    u8 recv = 0;
    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
        
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        recv = USART_ReceiveData(USART2);
        

        
    }

}


/**********************************************************
*   @fun：格式化串口输出
*   
*
*********************************************************/
void uprintf(USART_TypeDef* USARTx, char *fmt, ...)
{
	char buffer[128+1];
	u8 i = 0;
	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);  
	vsnprintf(buffer, 128+1, fmt, arg_ptr);
	USART_ClearFlag(USARTx,USART_FLAG_TXE);
	while ((i < 128) && buffer[i])
	{
		if(buffer[i] == '\n'){
			
			USART_SendData(USARTx,(u8)'\r');
			while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
			USART_SendData(USARTx,(u8)buffer[i++]);
		}else{
            USART_SendData(USARTx, (u8) buffer[i++]);
		}
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
	}
	va_end(arg_ptr);
 

}

void hexPrintf(USART_TypeDef* USARTx, char *data,int length){
    int i = 0;
    while(i != length){
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
		USART_SendData(USARTx,(u8)data[i++]);
    }
}

