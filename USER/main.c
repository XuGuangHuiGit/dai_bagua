#include "delay.h"
#include "global.h"
#include "sys.h"
#include "usart_u.h"	 
#include "circleQueue.h"
#include "can.h"
#include "cmd.h"
#include "time.h"
#include "string.h"


char* version = "software version:18.7.23";
float HardwareVersion;

u8 start_flag = DISABLE;

int PIT_period = 20;
int PIT_f = 0;

void Rcc_init(){
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
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

	PIT_f = 1000/PIT_period;
    Rcc_init();

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart_init(USART3 , 115200 ,ENABLE);
	cmd_init();
	IO_Init();
	TIM2_init(PIT_period);
	uprintf(USART3, "start\n");
    while(1){
        
    }
}

