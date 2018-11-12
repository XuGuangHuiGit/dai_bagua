#include "stm32f10x_can.h"
#include "global.h"
#include "circleQueue.h"


#define CAN1_ID         0x12     //stm��CAN���ߵı�ʶ��

#define CAN_MODE_X      CAN_Mode_Normal  //ģʽ

//CAN����ʱ�����������(��ʱ��Ϊ1Mbps)
#define CAN_SJW_X       CAN_SJW_1tq
#define CAN_BS1_X       CAN_BS1_3tq   //ʱ���1��ʱ�䵥Ԫ
#define CAN_BS2_X       CAN_BS2_2tq   //ʱ���2��ʱ�䵥Ԫ
#define CAN_PRESCALER_X 6     //��Ƶϵ��
/* speed= RCC_APB1PeriphClock/(CAN_SJW_X+CAN_BS1+CAN_BS2)/CAN_Prescaler
 */

//ʹ������IDģʽ
#define STDID           1
#define EXTID           0


//�б����ģʽʹ��ID,��ʱֻ��֧������ID
#define ID_filter1      404
#define ID_filter2      840


//�ж����ȼ�����
#define CAN1_NVIC_IRQPP CAN1_Priority              //CAN1�ж��������ȼ�
#define CAN1_NVIC_IRQSP CAN1_Priority              //CAN1�ж������ȼ�

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
int can_send_msg(u16 can_id,u8 *msg,u8 len);  //��������
int can_rcv_msg(void);   //������Ϣ
int can_add_callback(u16 can_id,void *msg_rcv_callback_func);
void USB_LP_CAN1_RX0_IRQHandler(void);
