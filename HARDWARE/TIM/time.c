#include "time.h"
#include "stm32f10x.h"
#include "usart_u.h"
#include "global.h"


int SteerPeriod = 20000;
int SteerPrescaler = 36;

int MotorPeriod = 4;
int MotorPrescaler = 2500;

//videoStruct video[STEERNUM];

/*定时中断*/
void TIM2_init(int Time_ms){
	int Period = 2*Time_ms;
	NVIC_InitTypeDef nvic_InitStructure;
	TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructInit(&tim_TimeBaseInitTypeDef);

	tim_TimeBaseInitTypeDef.TIM_Prescaler = 36000-1;  // 1M*2 
	tim_TimeBaseInitTypeDef.TIM_Period =Period; 
	tim_TimeBaseInitTypeDef.TIM_ClockDivision =TIM_CKD_DIV1;  //不分频 
	tim_TimeBaseInitTypeDef.TIM_CounterMode =TIM_CounterMode_Up;   //上数
	TIM_TimeBaseInit(TIM2,&tim_TimeBaseInitTypeDef);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);

	nvic_InitStructure.NVIC_IRQChannel = TIM2_IRQn;   
	nvic_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	nvic_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	nvic_InitStructure.NVIC_IRQChannelSubPriority = 0;   
	NVIC_Init(&nvic_InitStructure);  

	TIM_Cmd(TIM2, ENABLE); 
}

/*舵机初始化*/
void SteerInit(u16 group,u16 channel){
    
    GPIO_InitTypeDef GPIO_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    int gpioPin = 0;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
	
    if((group & groupA) == groupA){
        //tim4  B6789
        gpioPin = 0;
        if ((channel & channel1) == channel1) {
            gpioPin |= GPIO_Pin_6;
        }
        if ((channel & channel2) == channel2) {
            gpioPin |= GPIO_Pin_7;
        }
        if ((channel & channel3) == channel3) {
            gpioPin |= GPIO_Pin_8;
        }
        if ((channel & channel4) == channel4) {
            gpioPin |= GPIO_Pin_9;
        }
        GPIO_InitStructure.GPIO_Pin = gpioPin;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        tim_TimeBaseInitTypeDef.TIM_Prescaler = SteerPrescaler - 1; //1M
        tim_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
        tim_TimeBaseInitTypeDef.TIM_Period =SteerPeriod - 1;           
        tim_TimeBaseInitTypeDef.TIM_ClockDivision = 0;
        tim_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM4, &tim_TimeBaseInitTypeDef);
        
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_Pulse =0;								//duty=50%
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    //当为PWM模式2时，极性要反过来
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
        if ((channel & channel1) == channel1) {
            TIM_OC1Init(TIM4, &TIM_OCInitStructure);
        }
        if ((channel & channel2) == channel2) {
            TIM_OC2Init(TIM4, &TIM_OCInitStructure);
        }
        if ((channel & channel3) == channel3) {
            TIM_OC3Init(TIM4, &TIM_OCInitStructure);
        }
        if ((channel & channel4) == channel4) {
            TIM_OC4Init(TIM4, &TIM_OCInitStructure);
        }
        TIM_Cmd(TIM4, ENABLE);
    }
    
    if((group & groupB) == groupB){
        //tim5  A0123
        gpioPin = 0;
        if ((channel & channel1) == channel1) {
            gpioPin |= GPIO_Pin_0;
        }
        if ((channel & channel2) == channel2) {
            gpioPin |= GPIO_Pin_1;
        }
        if ((channel & channel3) == channel3) {
            gpioPin |= GPIO_Pin_2;
        }
        if ((channel & channel4) == channel4) {
            gpioPin |= GPIO_Pin_3;
        }
        GPIO_InitStructure.GPIO_Pin = gpioPin;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        tim_TimeBaseInitTypeDef.TIM_Prescaler = SteerPrescaler - 1; //1M
        tim_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
        tim_TimeBaseInitTypeDef.TIM_Period =SteerPeriod - 1;           
        tim_TimeBaseInitTypeDef.TIM_ClockDivision = 0;
        tim_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM5, &tim_TimeBaseInitTypeDef);
        
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_Pulse =0;								//duty=50%
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    //当为PWM模式2时，极性要反过来
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
        if ((channel & channel1) == channel1) {
            TIM_OC1Init(TIM5, &TIM_OCInitStructure);
        }
        if ((channel & channel2) == channel2) {
            TIM_OC2Init(TIM5, &TIM_OCInitStructure);
        }
        if ((channel & channel3) == channel3) {
            TIM_OC3Init(TIM5, &TIM_OCInitStructure);
        }
        if ((channel & channel4) == channel4) {
            TIM_OC4Init(TIM5, &TIM_OCInitStructure);
        }
        TIM_Cmd(TIM5, ENABLE);
    }
    
    if((group & groupC) == groupC){
        //tim3  A67 B01
        gpioPin = 0;
        if ((channel & channel1) == channel1) {
            gpioPin |= GPIO_Pin_6;
        }
        if ((channel & channel2) == channel2) {
            gpioPin |= GPIO_Pin_7;
        }
        GPIO_InitStructure.GPIO_Pin = gpioPin;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        gpioPin = 0;
        
        if ((channel & channel3) == channel3) {
            gpioPin |= GPIO_Pin_0;
        }
        if ((channel & channel4) == channel4) {
            gpioPin |= GPIO_Pin_1;
        }
        GPIO_InitStructure.GPIO_Pin = gpioPin;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        tim_TimeBaseInitTypeDef.TIM_Prescaler = SteerPrescaler - 1; //1M
        tim_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
        tim_TimeBaseInitTypeDef.TIM_Period =SteerPeriod - 1;           
        tim_TimeBaseInitTypeDef.TIM_ClockDivision = 0;
        tim_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM3, &tim_TimeBaseInitTypeDef);
        
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
        TIM_OCInitStructure.TIM_Pulse =0;								//duty=50%
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    //当为PWM模式2时，极性要反过来
        TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
        TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
        TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
        
        if ((channel & channel1) == channel1) {
            TIM_OC1Init(TIM3, &TIM_OCInitStructure);
        }
        if ((channel & channel2) == channel2) {
            TIM_OC2Init(TIM3, &TIM_OCInitStructure);
        }
        if ((channel & channel3) == channel3) {
            TIM_OC3Init(TIM3, &TIM_OCInitStructure);
        }
        if ((channel & channel4) == channel4) {
            TIM_OC4Init(TIM3, &TIM_OCInitStructure);
        }
        TIM_Cmd(TIM3, ENABLE);
    }
}


/*定时中断服务函数*/
void TIM2_IRQHandler(){
	int index = 0;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET ){
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);//清中断标志位
		//uprintf(USART3,"TIM2\n");
		if(Status.Wrong_timeout >0){
			Status.Wrong_timeout--;
			if(Status.Wrong_timeout == (int)(wrong_time * 0.65)){
				Set_allLight(0);
			}else if(Status.Wrong_timeout == (int)(wrong_time * 0.35)){
				Set_allLight(1);
			}
			
			if(Status.Wrong_timeout == 0){
				Reset_Line();
			}
		}	
		
		if(Status.currect_timeout >0){
			Status.currect_timeout--;
			if(Status.currect_flag == 1){
				//打开继电器 and
				Status.currect_flag = 0;
			}
			
			if(Status.currect_timeout == 0){
				//关闭继电器
				//reset
				Reset_Line();
			}
		}
	}
}



/*电机初始化*/
void MotorInit(u16 MotorNum){
    
    GPIO_InitTypeDef GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    int gpioPin = 0;
    int initFlag = 0;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    if((MotorNum & motor11) == motor11){
        initFlag = 1;
        gpioPin |= (GPIO_Pin_8 | GPIO_Pin_9);
    }
    if((MotorNum & motor12) == motor12){
        initFlag = 1;
        gpioPin |= (GPIO_Pin_10 | GPIO_Pin_11);
    }
    GPIO_InitStructure.GPIO_Pin = gpioPin;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
        
    tim_TimeBaseInitTypeDef.TIM_Prescaler = MotorPrescaler - 1; //1M
    tim_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
    tim_TimeBaseInitTypeDef.TIM_Period =MotorPeriod - 1;           
    tim_TimeBaseInitTypeDef.TIM_ClockDivision = 0;
    tim_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
    if( initFlag == 1){
        TIM_TimeBaseInit(TIM1, &tim_TimeBaseInitTypeDef);
    }
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =0;								//duty=50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    //当为PWM模式2时，极性要反过来
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    
    if((MotorNum & motor11) == motor11){
        TIM_OC1Init(TIM1, &TIM_OCInitStructure);
        TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    }
    if((MotorNum & motor11) == motor12){
        TIM_OC3Init(TIM1, &TIM_OCInitStructure);
        TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    }
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

//motor2 init
    initFlag = 0;
    if((MotorNum & motor21) == motor21){
        initFlag = 1;
        gpioPin |= (GPIO_Pin_6 | GPIO_Pin_7);
    }
    if((MotorNum & motor22) == motor22){
        initFlag = 1;
        gpioPin |= (GPIO_Pin_8 | GPIO_Pin_9);
    }
    GPIO_InitStructure.GPIO_Pin = gpioPin;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
        
    tim_TimeBaseInitTypeDef.TIM_Prescaler = MotorPrescaler - 1; //1M
    tim_TimeBaseInitTypeDef.TIM_CounterMode = TIM_CounterMode_Up;
    tim_TimeBaseInitTypeDef.TIM_Period =MotorPeriod - 1;           
    tim_TimeBaseInitTypeDef.TIM_ClockDivision = 0;
    tim_TimeBaseInitTypeDef.TIM_RepetitionCounter = 0;
    if( initFlag == 1){
        TIM_TimeBaseInit(TIM8, &tim_TimeBaseInitTypeDef);
    }
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =0;								//duty=50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    //当为PWM模式2时，极性要反过来
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    
    if((MotorNum & motor21) == motor21){
        TIM_OC1Init(TIM8, &TIM_OCInitStructure);
        TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    }
    if((MotorNum & motor22) == motor22){
        TIM_OC3Init(TIM8, &TIM_OCInitStructure);
        TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    }
    TIM_Cmd(TIM8, ENABLE);
    TIM_CtrlPWMOutputs(TIM8, ENABLE);
}

int getNum(int group, int channel){
	int i = 0;
	int g = 0, c = 0;
	for(i = 0; i < 4; i++){
		if(((group>>i) & 0x01) == 1){
			g = i;
		}
		if(((channel>>i) & 0x01) == 1){
			c = i;
		}
	}
	return (g*4 + c);
}

int getGroupBits(int num){
	int groupI = num/4;
	return 1<<groupI;
}

int getChannelBits(int num){
	int channelI = num%4;
	return 1<<channelI;
}
 

/*设置电机速度*/
void setMotor(int MotorNum , int Speed){
    int cmp;
    
    if((MotorNum & motor11) == motor11){
        if(Speed < 0){
            Speed *= -1;
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare1(TIM1,cmp);
            TIM_SetCompare2(TIM1,0);
        }else{
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare1(TIM1,0);
            TIM_SetCompare2(TIM1,cmp);
        }
    }
    if((MotorNum & motor12) == motor12){
        if(Speed < 0){
            Speed *= -1;
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare3(TIM1,cmp);
            TIM_SetCompare4(TIM1,0);
        }else{
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare3(TIM1,0);
            TIM_SetCompare4(TIM1,cmp);
        }
    }
    
    if((MotorNum & motor21) == motor21){
        if(Speed < 0){
            Speed *= -1;
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare1(TIM8,cmp);
            TIM_SetCompare2(TIM8,0);
        }else{
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare1(TIM8,0);
            TIM_SetCompare2(TIM8,cmp);
        }
        
    }
    if((MotorNum & motor22) == motor22){
        if(Speed < 0){
            Speed *= -1;
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare3(TIM8,cmp);
            TIM_SetCompare4(TIM8,0);
        }else{
            cmp = MotorPeriod*Speed/10000.0;
            TIM_SetCompare3(TIM8,0);
            TIM_SetCompare4(TIM8,cmp);
        }
    }
}
