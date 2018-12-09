#include "delay.h"
#include "global.h"
#include "sys.h"
#include "usart_u.h"	 
#include "circleQueue.h"
#include "can.h"
#include "cmd.h"
#include "time.h"
#include "string.h"


char* version = "sof";
float HardwareVersion;

u8 start_flag = DISABLE;

int PIT_period = 20;
int PIT_f = 0;

int right_time = 10;
int wrong_time = 2;

void Rcc_init(){
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB ±÷” πƒ‹ 
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_TIM1, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM2, ENABLE );
    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM3, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM4, ENABLE );
    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM5, ENABLE );
	
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_USART3, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_UART4, ENABLE );
    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_UART5, ENABLE );
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}
 
int main(void)
{	 
	int dex = 0;
	PIT_f = 1000/PIT_period;
    Rcc_init();

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart_init(USART3 , 115200 ,ENABLE);
	cmd_init();
	IO_Init();
	TIM2_init(PIT_period);
	
	LightLine_Init();
	
	uprintf(USART3, "start\n");
    while(1){
        if(LightLine[dex].Pass_Flag == 1){
			set_light(1<<dex, ON);
		}else{
			set_light(1<<dex, OFF);
		}
		dex ++; 
		
		if(dex >= LIGHT_NUM) dex = 0;
    }
}

