#include "global.h"
#include "usart_u.h"
#include "string.h"
#include "time.h"
#include "delay.h"

lightStruct light[LIGHT_NUM];
int relay_timeout = 0;



void _gpio_init(GPIO_TypeDef* GPIOx ,GPIOMode_TypeDef GPIO_MODE, GPIOSpeed_TypeDef GPIO_SPEED, uint16_t pin){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}


void EXIT_IRQ_Init(GPIO_TypeDef* GPIOx ,GPIOMode_TypeDef GPIO_MODE, GPIOSpeed_TypeDef GPIO_SPEED, uint16_t pin, u8 IRQChannel, uint32_t Exit_line ,EXTITrigger_TypeDef Exit_Trigger){
	_gpio_init(GPIOx ,GPIO_MODE,GPIO_SPEED, pin);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	u8 pinSource;
	u8 pinNUM;
	if (GPIOx == GPIOA) pinSource = GPIO_PortSourceGPIOA;
	else if (GPIOx == GPIOB) pinSource = GPIO_PortSourceGPIOB;
	else if (GPIOx == GPIOC) pinSource = GPIO_PortSourceGPIOC;
	else return;
	
	if(pin == GPIO_Pin_0 ) pinNUM = GPIO_PinSource0;
	else if(pin == GPIO_Pin_1 ) pinNUM = GPIO_PinSource1;
	else if(pin == GPIO_Pin_2 ) pinNUM = GPIO_PinSource2;
	else if(pin == GPIO_Pin_3 ) pinNUM = GPIO_PinSource3;
	else if(pin == GPIO_Pin_4 ) pinNUM = GPIO_PinSource4;
	else if(pin == GPIO_Pin_5 ) pinNUM = GPIO_PinSource5;
	else if(pin == GPIO_Pin_6 ) pinNUM = GPIO_PinSource6;
	else if(pin == GPIO_Pin_7 ) pinNUM = GPIO_PinSource7;
	else if(pin == GPIO_Pin_8 ) pinNUM = GPIO_PinSource8;
	else if(pin == GPIO_Pin_9 ) pinNUM = GPIO_PinSource9;
	else if(pin == GPIO_Pin_10 ) pinNUM = GPIO_PinSource10;
	else if(pin == GPIO_Pin_11 ) pinNUM = GPIO_PinSource11;
	else if(pin == GPIO_Pin_12 ) pinNUM = GPIO_PinSource12;
	else if(pin == GPIO_Pin_13 ) pinNUM = GPIO_PinSource13;
	else if(pin == GPIO_Pin_14 ) pinNUM = GPIO_PinSource14;
	else if(pin == GPIO_Pin_15 ) pinNUM = GPIO_PinSource15;
	
	GPIO_EXTILineConfig(pinSource, pinNUM);
    
    EXTI_InitStruct.EXTI_Line = Exit_line;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = Exit_Trigger;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
    NVIC_Init(&NVIC_InitStructure);
}

void IO_Init(){
	//继电器
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_12);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_13);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_14);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_15);
	
	//灯   使用B
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_0);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_1);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_9);

	
	//一下是中断的配置
	/*使用A组*/
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_0, EXTI0_IRQn,EXTI_Line0 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_1, EXTI1_IRQn,EXTI_Line1 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_2, EXTI2_IRQn,EXTI_Line2 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_3, EXTI3_IRQn,EXTI_Line3 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_4, EXTI4_IRQn,EXTI_Line4 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_5, EXTI9_5_IRQn,EXTI_Line5 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_6, EXTI9_5_IRQn,EXTI_Line6 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_7, EXTI9_5_IRQn,EXTI_Line7 ,EXTI_Trigger_Rising);
	
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_8, EXTI9_5_IRQn,EXTI_Line8 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_9, EXTI9_5_IRQn,EXTI_Line9 ,EXTI_Trigger_Rising);

	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_10, EXTI15_10_IRQn,EXTI_Line10 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_11, EXTI15_10_IRQn,EXTI_Line11 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_12, EXTI15_10_IRQn,EXTI_Line12 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_13, EXTI15_10_IRQn,EXTI_Line13 ,EXTI_Trigger_Rising);
	EXIT_IRQ_Init(GPIOC ,GPIO_Mode_IPD, GPIO_Speed_50MHz, GPIO_Pin_14, EXTI15_10_IRQn,EXTI_Line14 ,EXTI_Trigger_Rising);
	/*使用B组*/

	
}

/***
设置继电器状态

***/
void set_relay(u8 relay, u8 state){
	if((relay&relay1) == relay1){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		}
	}
	
	if((relay&relay2) == relay2){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_13);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		}
	}
	
	if((relay&relay3) == relay3){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_14);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		}
	}
	
	if((relay&relay4) == relay4){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_15);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		}
	}
}

/***
设置gangqin的灯

***/
void set_light(u16 ligh, u8 state){
	if((ligh&light1) == light1){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		}
	}
	
	if((ligh&light2) == light2){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		}
	}
	
	if((ligh&light3) == light3){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		}
	}
	
	if((ligh&light4) == light4){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_11);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		}
	}
	if((ligh&light5) == light5){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_12);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_12);
		}
	}
	
	if((ligh&light6) == light6){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		}
	}
	
	if((ligh&light7) == light7){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
	}
	
	if((ligh&light8) == light8){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		}
	}
}


/*跳关*/
void EXTI0_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line0)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line0);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == TOUCH_LEVEL){
			//set_relay(relay1 |relay4, ON);
			uprintf(USART3, "C0\n");
		}
	}
	
}


/*外部中段*/

void EXTI1_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line1)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line1);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == TOUCH_LEVEL){
			uprintf(USART3, "C1\n");
		}
	}
}

void EXTI2_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line2);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == TOUCH_LEVEL){
			uprintf(USART3, "C2\n");
		}
	}
}

void EXTI3_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line3);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == TOUCH_LEVEL){
			uprintf(USART3, "C3\n");
		}
	}
}




/*  无源开关4  */
void EXTI4_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line4)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line4);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == TOUCH_LEVEL){
			uprintf(USART3, "C4\n");
		}
	}
}

/*  无源开关5  */
void EXTI9_5_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line5)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line5);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == TOUCH_LEVEL){
			uprintf(USART3, "C5\n");

		}
	}
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line6);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == TOUCH_LEVEL){
			uprintf(USART3, "C6\n");
		}
	}
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line7);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == TOUCH_LEVEL){
			uprintf(USART3, "C7\n");
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line8);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) == TOUCH_LEVEL){
			uprintf(USART3, "C8\n");
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line9);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9) == TOUCH_LEVEL){
			uprintf(USART3, "C9\n");
		}
	}
	
}


/*  无源开关5  */
void EXTI15_10_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line10)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line10);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10) == TOUCH_LEVEL){
			uprintf(USART3, "C10\n");

		}
	}
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line11);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11) == TOUCH_LEVEL){
			uprintf(USART3, "C11\n");
		}
	}
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line12);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == TOUCH_LEVEL){
			uprintf(USART3, "C12\n");
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line13);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == TOUCH_LEVEL){
			uprintf(USART3, "C13\n");
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line14);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == TOUCH_LEVEL){
			uprintf(USART3, "C14\n");
		}
	}
	
}

