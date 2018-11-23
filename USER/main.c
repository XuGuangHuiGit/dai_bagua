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

char *mima 			= "5312\0"; //密码
u8 width	 		= 4;		//密码位数，务必与上面一致 最大为8
int timeout			= 10;		//密码输入时的超时时间，单位秒
int RelayTimeout	=10;		//密码正确后，继电器自动关闭时间，单位秒
float rongcuoTime	=0.6;		//防止一次弹弦后，多次接受同一个信号，单位秒

u8 start_flag = DISABLE;

int PIT_period = 20;
int PIT_f = 0;

void Rcc_init(){
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
 
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
 
void video_Init(){
	int i =0;
	for(i = 0; i < STEERNUM; i++){
//		video[i].CanGet_Flag = ENABLE;
//		video[i].time = -1;
//		video[i].timeout = -1;
//		video[i].touched = UNTOUCHED;
		
		light[i].light_Flag = 0;
		light[i].pwdWrong_Flag = 0;
		light[i].timeout = -1;
			
	}
	
	PassWord.errorPWD_Flag = 0;
	PassWord.index = 0;
	
	PassWord.width = width;
	memcpy(PassWord.PWD, mima, PassWord.width);
	memcpy(PassWord.pwd , "0000000\0", PassWord.width);
	
}


int main(void)
{	 
	int ind = 0;
	PIT_f = 1000/PIT_period;
    Rcc_init();
	IRQ_tt[0].GPIOx = GPIOA;
	IRQ_tt[0].GPIO_Pin = GPIO_Pin_1;
	IRQ_tt[1].GPIOx = GPIOA;
	IRQ_tt[1].GPIO_Pin = GPIO_Pin_2;
	IRQ_tt[2].GPIOx = GPIOA;
	IRQ_tt[2].GPIO_Pin = GPIO_Pin_3;
	IRQ_tt[3].GPIOx = GPIOA;
	IRQ_tt[3].GPIO_Pin = GPIO_Pin_4;
	IRQ_tt[4].GPIOx = GPIOA;
	IRQ_tt[4].GPIO_Pin = GPIO_Pin_5;
	IRQ_tt[5].GPIOx = GPIOA;
	IRQ_tt[5].GPIO_Pin = GPIO_Pin_6;
	IRQ_tt[6].GPIOx = GPIOA;
	IRQ_tt[6].GPIO_Pin = GPIO_Pin_7;
	IRQ_tt[7].GPIOx = GPIOA;
	IRQ_tt[7].GPIO_Pin = GPIO_Pin_8;
	for(ind= 0; ind<STEERNUM;ind++){
		HighDelay[ind].getH_flag = 0;
		HighDelay[ind].time = 0;
		HighDelay[ind].below_flag = 0;
	}
	ind = 0;
	delay_init();
	video_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart_init(USART3 , 115200 ,ENABLE);
	cmd_init();
	IO_Init();
	//set_relay(relay2, ON);
	TIM2_init(PIT_period);
	uprintf(USART3, "start sys\ndefault pwd %s\nnow pwd %s\n", PassWord.PWD, PassWord.pwd);
	
    while(1){
        
		if(light[ind].light_Flag == 1){
			//she light
			set_light(1<<ind,ON);
		}else{
			//she unlight
			if(light[ind].liushui_flag == 0){
				set_light(1<<ind,OFF);
			}else{
				set_light(1<<ind,ON);
			}
		}
		
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9) == 1){
			start_flag = ENABLE;
		}else{
			start_flag = DISABLE;
		}
		ind ++;
		if(ind == STEERNUM){
			ind = 0;
		}
    }
}

