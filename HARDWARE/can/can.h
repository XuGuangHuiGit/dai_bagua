#include "stm32f10x_can.h"
#include "global.h"
#include "circleQueue.h"


#define CAN1_ID         0x12     //stm的CAN总线的标识符

#define CAN_MODE_X      CAN_Mode_Normal  //模式

//CAN总线时序和速率配置(此时配为1Mbps)
#define CAN_SJW_X       CAN_SJW_1tq
#define CAN_BS1_X       CAN_BS1_3tq   //时间段1的时间单元
#define CAN_BS2_X       CAN_BS2_2tq   //时间段2的时间单元
#define CAN_PRESCALER_X 6     //分频系数
/* speed= RCC_APB1PeriphClock/(CAN_SJW_X+CAN_BS1+CAN_BS2)/CAN_Prescaler
 */

//使用哪种ID模式
#define STDID           1
#define EXTID           0


//列表过滤模式使用ID,暂时只能支持两个ID
#define ID_filter1      404
#define ID_filter2      840


//中断优先级设置
#define CAN1_NVIC_IRQPP CAN1_Priority              //CAN1中断抢断优先级
#define CAN1_NVIC_IRQSP CAN1_Priority              //CAN1中断子优先级

#define CANX        CAN1
#define CAN_ID      CAN1_ID

#define ODODIR_CANID        404
#define ODOCNT_CANID        840



typedef struct{
    u16 can_id;
    void (*msg_rcv_callback)(CanRxMsg *can_rx_msg);
}can_callback_struct;



int can_init(int baud);
void can_gpio_config(void);
void can_nvic_config(void);
int can_send_msg(u16 can_id,u8 *msg,u8 len);  //发送邮箱
int can_rcv_msg(void);   //接收信息
int can_add_callback(u16 can_id,void *msg_rcv_callback_func);
void USB_LP_CAN1_RX0_IRQHandler(void);
