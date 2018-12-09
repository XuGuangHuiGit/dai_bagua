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

#define POINT_NUM   12
#define LIGHT_NUM   18
#define IRQ_TOUCH_STATUS_HIGH	1
#define IRQ_TOUCH_STATUS_LOW	0
#define TOUCH_LEVEL	IRQ_TOUCH_STATUS_HIGH

#define UNSTART		-101

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
	light8 = 0x80,
	light9 = 0x100,
	light10 = 0x200,
    light11 = 0x400,
	light12 = 0x800,
	light13 = 0x1000,
	light14 = 0x2000,
    light15 = 0x4000,
	light16 = 0x8000,
	light17 = 0x10000,
	light18 = 0x20000
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


typedef struct {
	u8 liushui_flag;
	u8 pwdWrong_Flag;
	u8 light_Flag;
	int timeout;
}lightStruct;

typedef struct {
	int small;
	int big;
	u8 Pass_Flag;
	
}lightDAI;

///����һ����������ṹ
struct MoveStruct{
	int front;
	int now;
	u8 steps;
	
};

///����һ��״̬�ṹ
struct StatusStruct{
	u8 currect_flag;
	u8 Wrong_timeout;
	u8 currect_timeout;
	
};


//����
extern struct StatusStruct Status; 
extern struct MoveStruct Move;
extern lightDAI LightLine[LIGHT_NUM];
extern int PIT_period;
extern int PIT_f;
extern u8 start_flag;


extern int right_time ;
extern int wrong_time;
extern float rongcuoTime;
extern int timeout;
extern char* version ;//�������ﶨ�壬���ڱ�������汾��
extern float HardwareVersion;//�������ﶨ�� �����ڱ���Ӳ���汾��
extern link_list steerLink;
extern u8 MotorDone_Flag;


void LightLine_Init();
void Set_allLight(u8 sta);
void Reset_Line();
u8 updateLine(int front, int back);
void set_light(u32 ligh, u8 state);
void _gpio_init(GPIO_TypeDef* GPIOx ,GPIOMode_TypeDef GPIO_MODE, GPIOSpeed_TypeDef GPIO_SPEED, uint16_t pin);
void set_relay(u8 relay, u8 state);
void IO_Init(void);



#endif

