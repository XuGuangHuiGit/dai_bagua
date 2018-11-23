#include "global.h"
#include "usart_u.h"
#include "string.h"
#include "time.h"
#include "delay.h"

PWDStruct PassWord;
lightStruct light[STEERNUM];
int relay_timeout = 0;

BeHDelay HighDelay[STEERNUM];
int holdTime ;


void _gpio_init(GPIO_TypeDef* GPIOx ,GPIOMode_TypeDef GPIO_MODE, GPIOSpeed_TypeDef GPIO_SPEED, uint16_t pin){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void IO_Init(){
	holdTime = 3*PIT_f;
	
	EXTI_InitTypeDef EXTI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

	//继电器
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_12);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_13);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_14);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_15);
	
	//钢琴的灯   使用B
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_0);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_1);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_9);
	//_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_3);
	//_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_4);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_6);
	_gpio_init(GPIOB ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_7);
	
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_11);
	_gpio_init(GPIOA ,GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_12);

	
	//一下是中断的配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
    NVIC_Init(&NVIC_InitStructure);
	
	
    //   PIN A1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	//   PIN A2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	// PIN C3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	
	
	//pin   A4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line4;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	/////pin A5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
////    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line5;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	/////pin A6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line6;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
//	
	/////pin A7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line7;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	
	//A8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
//    
//    EXTI_InitStruct.EXTI_Line = EXTI_Line8;
//    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_Init(&EXTI_InitStruct);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
//    NVIC_Init(&NVIC_InitStructure);
	//A9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;// | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line9;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStruct);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = EXIT1_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = EXIT1_Priority;
    NVIC_Init(&NVIC_InitStructure);
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


void PWDReset(){
	PassWord.index =0;
	PassWord.timeout = -1;
	memset(PassWord.pwd,0,4);
}

int getOffest(int num){
	
	if(num == 0) return 0;
	if(num == 1) return 4;
	if(num == 2) return 1;
	if(num == 3) return 2;
	
	return 0;
	
}

void getSign(int channel){
	channel -=1;
	int i = 0;
	//if(video[channel].CanGet_Flag == ENABLE){
//		video[channel].touched = TOUCHED;
//		video[channel].time = rongcuoTime*PIT_f;
//		video[channel].timeout = video[channel].time;
//		video[channel].CanGet_Flag = DISABLE;
#ifdef DEBUG
		uprintf(USART3, "E%d\n", channel+1);
#endif
		PassWord.pwd[PassWord.index] = channel +49;
		channel = (getOffest(PassWord.index) + channel)%8;
		light[channel].light_Flag = 1;
		light[channel].timeout = 600*PIT_f;
		
		PassWord.index++;
		
		PassWord.timeout = timeout*PIT_f;
		if(PassWord.index == PassWord.width){
			//check pwd
			if(strcmp(PassWord.PWD , PassWord.pwd) == 0){
				//correct pwd
				for(i = 0; i<STEERNUM; i++){
					if(light[channel].timeout >10)
						light[channel].timeout = RelayTimeout*PIT_f;
				}
				PassWord.errorPWD_Flag = 0;
				PWDReset();
				set_relay(relay1 |relay4, ON);
				relay_timeout = RelayTimeout*PIT_f + 120*PIT_f;
				//uprintf(USART3, "cp\n");
			}else{
				//error pwd
				PassWord.errorPWD_Flag = 1;
				PWDReset();
				//uprintf(USART3, "pp\n");
			}
		}
	//}	
}

/*跳关*/
void EXTI0_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line0)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line0);
		delay_ms(2);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0){
			set_relay(relay1 |relay4, ON);
			relay_timeout = RelayTimeout*PIT_f;
			//uprintf(USART3, "jump\n");
		}
	}
	
}


void set_gigh(int channel){
	//HighDelay[channel].flag = 1;
	HighDelay[channel].time = 0;
}


/*外部中段*/

void EXTI1_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line1)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line1);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0){
			//进入
			//set_gigh(1);
			if(HighDelay[0].time > holdTime){
				//HighDelay[1].flag = 0;
				HighDelay[0].time = 0;
				getSign(1);
			}
		}
	}
}

void EXTI2_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line2)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line2);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0){
			//进入
			//set_gigh(2);
			//uprintf(USART3,"%d\n",HighDelay[1].time);;
			if(HighDelay[1].time > holdTime){
				//HighDelay[2].flag = 0;
				HighDelay[1].time = 0;
				getSign(2);
			}
		}
	}
}

void EXTI3_IRQHandler(void){
    
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line3);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0){
			//进入
			//set_gigh(3);
			if(HighDelay[2].time > holdTime){
				//HighDelay[3].flag = 0;
				HighDelay[2].time = 0;
				getSign(3);
			}
		}
	}
}




/*  无源开关4  */
void EXTI4_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line4)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line4);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0){
			//进入
			//set_gigh(4);
			if(HighDelay[3].time > holdTime){
				//HighDelay[4].flag = 0;
				HighDelay[3].time = 0;
				getSign(4);
			}
			
		}
	}
}

/*  无源开关5  */
void EXTI9_5_IRQHandler(void){
	
    if(EXTI_GetITStatus(EXTI_Line5)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line5);
		//delay_ms(1);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0){
			//进入
			//set_gigh(5);
			if(HighDelay[4].time > holdTime){
				//HighDelay[5].flag = 0;
				HighDelay[4].time = 0;
				getSign(5);
			}
		}
	}
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line6);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0){
			//进入
			//set_gigh(6);
			if(HighDelay[5].time > holdTime){
				//HighDelay[6].flag = 0;
				HighDelay[5].time = 0;
				getSign(6);
			}
		}
	}
	if(EXTI_GetITStatus(EXTI_Line7)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line7);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0){
			//进入
			//set_gigh(7);
			if(HighDelay[6].time > holdTime){
				//HighDelay[7].flag = 0;
				HighDelay[6].time = 0;
				getSign(7);
			}
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line8)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line8);
		//delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0){
			//进入
			//set_gigh(8);
			if(HighDelay[7].time > holdTime){
				//HighDelay[8].flag = 0;
				HighDelay[7].time = 0;
				getSign(8);
			}
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
        EXTI_ClearITPendingBit(EXTI_Line9);
		delay_ms(1);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 0){
			//start
			start_flag = ENABLE;
		}
	}
//	
//	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
//        EXTI_ClearITPendingBit(EXTI_Line9);
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 1){
//			getSign(7);
//		}
//	}
}
