#include "global.h"
#include "usart_u.h"
#include "string.h"
#include "time.h"
#include "delay.h"

#define DEBUG

lightDAI LightLine[LIGHT_NUM];
int relay_timeout = 0;

struct MoveStruct Move;
struct StatusStruct Status;

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
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_0);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_1);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_2);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_3);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_4);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_6);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_7);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_8);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_9);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_10);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_11);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_12);
	
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_3);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_4);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_6);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_7);

	
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
void set_light(u32 ligh, u8 state){
	if((ligh&light1) == light1){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		}
	}
	
	if((ligh&light2) == light2){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		}
	}
	
	if((ligh&light3) == light3){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		}
	}
	
	if((ligh&light4) == light4){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		}
	}
	if((ligh&light5) == light5){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_14);
		}
	}
	
	if((ligh&light6) == light6){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
	}
	
	if((ligh&light7) == light7){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		}
	}
	
	if((ligh&light8) == light8){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
	}
	
	if((ligh&light9) == light9){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		}
	}
	
	if((ligh&light10) == light10){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_9);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);
		}
	}
	
	if((ligh&light11) == light11){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_10);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
		}
	}
	
	if((ligh&light12) == light12){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_11);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		}
	}
	
	if((ligh&light13) == light13){
		if(state == ON){
			GPIO_SetBits(GPIOA, GPIO_Pin_12);
		}else{
			GPIO_ResetBits(GPIOA, GPIO_Pin_12);
		}
	}
	
	if((ligh&light14) == light14){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_3);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_3);
		}
	}
	
	if((ligh&light15) == light15){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_4);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_4);
		}
	}
	
	if((ligh&light16) == light16){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		}
	}
	
	if((ligh&light17) == light17){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
	}
	
	if((ligh&light18) == light18){
		if(state == ON){
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}else{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		}
	}
}


void Go_Step(int now){
	if(Move.front == UNSTART){
		Move.front = now;
	}else{
		if(Move.front == now) return;
		
		
		if(updateLine(Move.front, now)){
			Move.front = now;
			Move.steps ++;
			#ifdef DEBUG
			uprintf(USART3, "N:%d, %d\n",Move.front, now);
			#endif
			if(Move.steps == 18){
				//任务完成，cheer
				uprintf(USART3, "success\n");
				Status.currect_flag = 1;
				Status.currect_timeout = right_time*PIT_f;
				Status.Wrong_timeout = 0;
			}
		}else{
			//密码错误
			#ifdef DEBUG
			uprintf(USART3, "fail\n");
			#endif
			Status.currect_flag = 0;
			Status.Wrong_timeout = wrong_time*PIT_f;
			Status.currect_timeout = 0;
			Set_allLight(1);
		}
		
		
		
	}
}





/*跳关*/
void EXTI0_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line0)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line0);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == TOUCH_LEVEL){
			//set_relay(relay1 |relay4, ON);
			#ifdef DEBUG
			uprintf(USART3, "C0\n");
			#endif
			Go_Step(0);
		}
	}
	
}


/*外部中段*/

void EXTI1_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line1)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line1);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C1\n");
			#endif
			Go_Step(1);
		}
	}
}

void EXTI2_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line2);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C2\n");
			#endif
			Go_Step(2);
		}
	}
}

void EXTI3_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line3);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C3\n");
			#endif
			Go_Step(3);
		}
	}
}




/*  无源开关4  */
void EXTI4_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line4)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line4);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C4\n");
			#endif
			Go_Step(4);
		}
	}
}

/*  无源开关5  */
void EXTI9_5_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line5)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line5);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C5\n");
			#endif
			Go_Step(5);

		}
	}
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line6);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C6\n");
			#endif
			Go_Step(6);
		}
	}
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line7);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C7\n");
			#endif
			Go_Step(7);
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line8);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C8\n");
			#endif
			Go_Step(8);
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line9);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C9\n");
			#endif
			Go_Step(9);
		}
	}
	
}


/*  无源开关5  */
void EXTI15_10_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line10)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line10);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C10\n");
			#endif
			Go_Step(10);
		}
	}
	if(EXTI_GetITStatus(EXTI_Line11)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line11);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C11\n");
			#endif
			Go_Step(11);
		}
	}
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line12);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C12\n");
			#endif
			//Go_Step(12);
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line13);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C13\n");
			#endif
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line14)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line14);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == TOUCH_LEVEL){
			#ifdef DEBUG
			uprintf(USART3, "C14\n");
			#endif
		}
	}
	
}




#include "stdlib.h"




//初始化灯带结构体
void LightLine_Init(){
	int L_i = 0;
	uprintf(USART3, "init line : %d", L_i);
	Move.front = UNSTART;
	Move.now = UNSTART;
	Move.steps = 0;
	
	for(int i = 0; i < POINT_NUM - 1; i++)
	{
		LightLine[L_i].small = i;
		LightLine[L_i].big = i+1;
		LightLine[L_i].Pass_Flag = 0;
		L_i++;
		if(i%2 == 1){
			LightLine[L_i].small = i;
			LightLine[L_i].big = i+2;
			LightLine[L_i].Pass_Flag = 0;
			L_i++;
		}
	}
	LightLine[L_i].small = -1;
	LightLine[L_i].big = 0;
	LightLine[L_i].Pass_Flag = 0 ;
	L_i++;
	LightLine[L_i].small = -1;
	LightLine[L_i].big = 1;
	LightLine[L_i].Pass_Flag = 0 ;
	uprintf(USART3, "init line : %d", L_i);

}


//重置灯带状态
void Reset_Line(){
	#ifdef DEBUG
	uprintf(USART3, "reset LIne\n");
	#endif
	Set_allLight(0);
	
	Move.front = UNSTART;
	Move.now = UNSTART;
	Move.steps = 0;
	
	Status.currect_flag = 0;
	Status.currect_timeout = 0;
	Status.Wrong_timeout = 0;
}


//set all light light
void Set_allLight(u8 sta){
	for(int i = 0; i<LIGHT_NUM; i++){
		LightLine[i].Pass_Flag = sta;
	}
}


//更新并标记已走过的点
u8 updateLine(int front, int back){
	if(front == 11 && (back == 0 ||back == 1 )){
		front = -1 ;
	}
	
	if(back == 11 && (front == 0 ||front == 1 )){
		front = -1 ;
	}
	
	if(front%2 == 0){
		//偶数，定点，两个连接点
		if(abs(front - back) != 1){
			return 0;
		}
	}
	
	if(front%2 == 1){
		//偶数，定点，两个连接点
		if(abs(front - back) >2){
			return 0;
		}
	}
	
	int min = (front>back)?back:front;
	int max = (front>back)?front:back;
	
	for(int i = 0; i<LIGHT_NUM; i++){
		if(LightLine[i].small == min && LightLine[i].big == max){
			if(LightLine[i].Pass_Flag == 0){
				LightLine[i].Pass_Flag = 1;
				return 1;
			}else{
				return 0;
			}	
		}
	}
	
	return 0;
}













