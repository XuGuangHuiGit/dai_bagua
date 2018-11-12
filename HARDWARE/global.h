#ifndef __GLOBAL__H
#define __GLOBAL__H

//��һЩ��Ҫȫ��ʹ�õĶ�������������

#include "sys.h"
#include "list.h"

enum IRQPriority{
    
    USART1_Priority,
    
    USART3_Priority, //����ͬ����3
    
    EXIT0_Priority,//�ⲿ�ж�0 ��PPSʹ��
    
    TIM2_Priority,//��ʱ��2�����ڷ�Ƶʱ�Ӹ�GPS���Լ���������ϵͳʱ��
    
    CAN1_Priority,
    
    EXIT1_Priority,//�ⲿ�ж�1 ��IMU��DR����ʹ��
    
    USART2_Priority,
    
};

#define STEERNUM   8
//У�鴮�ڲ�����
#define UART_BAUD_ASSERT(BAUD) (((BAUD) == 9600) || \
                                ((BAUD) == 38400) || \
                                ((BAUD) == 115200) || \
                                ((BAUD) == 230400))

#define DEBUG
typedef enum {
    light1 = 0x01,
    light2 = 0x02,
    light3 = 0x04,
	light4 = 0x08,
	light5 = 0x10,
    light6 = 0x20,
	light7 = 0x40,
	light8 = 0x80
}lightGroup;

typedef enum {
    relay1 = 0x01,
    relay2 = 0x02,
    relay3 = 0x04,
	relay4 = 0x08
}relayGroup;
#define ON	1
#define OFF	0

typedef enum {
    input1 = 0x01,
    input2 = 0x02,
    input3 = 0x04,
	input4 = 0x08
}inputGroup;
#define HIGH 	1
#define LOW		0

enum{
	TOUCHED = 1,
	UNTOUCHED = 0
};

typedef struct{
	u8 touched;
	int time;
	int timeout;
	u8 CanGet_Flag;

}videoStruct;

typedef struct{
	char pwd[8];
	char index;
	char PWD[8];
	char errorPWD_Flag;
	int timeout;
	u8 width;
}PWDStruct;

typedef struct {
	u8 liushui_flag;
	u8 pwdWrong_Flag;
	u8 light_Flag;
	int timeout;
}lightStruct;

typedef struct{
	int time;
	//u8 flag;
}BeHDelay;

typedef struct{
	GPIO_TypeDef* GPIOx; 
	uint16_t GPIO_Pin;
}IRQ_t;


//����
extern int PIT_period;
extern int PIT_f;
extern u8 start_flag;
extern IRQ_t IRQ_tt[STEERNUM];
extern float rongcuoTime;
extern int timeout;
extern PWDStruct PassWord;
extern lightStruct light[STEERNUM];
//extern videoStruct video[STEERNUM];
extern BeHDelay HighDelay[STEERNUM];
extern char* version ;//�������ﶨ�壬���ڱ�������汾��
extern float HardwareVersion;//�������ﶨ�� �����ڱ���Ӳ���汾��
extern link_list steerLink;
extern u8 MotorDone_Flag;
extern int RelayTimeout;
extern int relay_timeout;

void PWDReset(void);
void set_light(u16 ligh, u8 state);
void _gpio_init(GPIO_TypeDef* GPIOx ,GPIOMode_TypeDef GPIO_MODE, GPIOSpeed_TypeDef GPIO_SPEED, uint16_t pin);
void set_relay(u8 relay, u8 state);
void IO_Init(void);



#endif

