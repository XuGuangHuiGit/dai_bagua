#include "can.h"
#include "usart_u.h"



static void (*msg_rcv_callback)(CanRxMsg *can_rx_msg);
static CanRxMsg g_can_rx_msg;

//Ϊ������ٶȣ���ʱ������
#define CAN_MAIL_CONTENT 1
can_callback_struct can_cb_array[CAN_MAIL_CONTENT]; 

/******************************************************
 * @fun��can���߳�ʼ��
 * @return����ʼ���ɹ��򷵻�1
 *  
 ******************************************************/
int can_init(int baud)
{
    int i;
	
    int CAN_PRESCALER;
    CAN_InitTypeDef can_init_struct;
	CAN_FilterInitTypeDef can_FilterInitTypeDef;
	
    if(baud >1000000 || baud <1000){
        uprintf(USART3,"can baud set error : %d\nplease check config and reboot in usart3 with 115200\n" , baud );
        while(1);//���ô��������￨ס�ȴ��������ú�����
    }
    
    CAN_PRESCALER = 6*1000000/baud;
    
    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_CAN1,  ENABLE );
    can_gpio_config();
    CAN_DeInit(CANX); 
    CAN_StructInit(&can_init_struct);
    can_init_struct.CAN_TTCM = DISABLE;  //��ʱ�䴥��ͨ��ģʽ
    can_init_struct.CAN_AWUM = DISABLE;  //˯��ģʽͨ���������
    can_init_struct.CAN_ABOM = ENABLE;  //����Զ����߹���
    can_init_struct.CAN_NART = DISABLE;   //��ֹ�����Զ�����
    can_init_struct.CAN_RFLM = DISABLE;  //���Ĳ��������µĸ��Ǿɵ�
    can_init_struct.CAN_TXFP = ENABLE;  //���ȼ��ɱ��ı�ʶ������
    can_init_struct.CAN_Mode = CAN_MODE_X;     //ģʽ����
    can_init_struct.CAN_SJW  = CAN_SJW_X;     //ͬ����Ծ���
    can_init_struct.CAN_BS1  = CAN_BS1_X; //��ΧCAN_BS1_1tq ~ CAN_BS1_16tq
    can_init_struct.CAN_BS2  = CAN_BS2_X; //��ΧCAN_BS1_1tq ~ CAN_BS1_16tq
    can_init_struct.CAN_Prescaler = CAN_PRESCALER;  //��Ƶϵ��(Fdiv)CAN_PRESCALER_X
    CAN_Init(CANX,&can_init_struct);


	can_FilterInitTypeDef.CAN_FilterNumber = 0;
	can_FilterInitTypeDef.CAN_FilterMode = CAN_FilterMode_IdList;
	can_FilterInitTypeDef.CAN_FilterScale = CAN_FilterScale_32bit;
	can_FilterInitTypeDef.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	can_FilterInitTypeDef.CAN_FilterMaskIdHigh = ID_filter1<<5;
    can_FilterInitTypeDef.CAN_FilterMaskIdLow = CAN_ID_STD;
    can_FilterInitTypeDef.CAN_FilterIdLow = CAN_ID_STD;
    can_FilterInitTypeDef.CAN_FilterIdHigh = ID_filter2<<5;
	can_FilterInitTypeDef.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&can_FilterInitTypeDef);
	
    CAN_ITConfig(CANX,CAN_IT_FMP0,ENABLE);  //FIFO0��Ϣ�Һ��ж�����

    for(i = 0;i < CAN_MAIL_CONTENT;i++){
        can_cb_array[i].can_id = i;
        can_cb_array[i].msg_rcv_callback = 0;
    }
    can_nvic_config();
    return 1;
}

/******************************************************
*   @fun�����Ӷ�Ӧ��ʶ����CALLBACK����
*   @param ��u8 can_id,������Ϣ��CALLBACK������Ӧ�ı�ʶ��
         void *msg_rcv_callback_fuc �ʼ����ջص�������ָ�룬ÿ�����յ�����Ҫ��
 *       ��Ϣʱ���Զ����øú�����ע�⣺�������ڽ����ж��������������ģ����Ը�
 *       ��������ִ��̫�á�����ú���ָ��ΪNULL����ʹ���ʼ������жϡ�
 * @return��-1,�Ѿ����ں���
 *          1,�ɹ����Ӻ���
 ******************************************************/
int can_add_callback(u16 can_id,void *msg_rcv_callback_func){
    if(can_cb_array[can_id].msg_rcv_callback != 0){
        return -1;
    }
    can_cb_array[can_id].msg_rcv_callback = msg_rcv_callback_func;
    return 1;
}


void can_gpio_config(){
	
    GPIO_InitTypeDef gpio_init_stru;
    gpio_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init_stru.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA,&gpio_init_stru);
	
	gpio_init_stru.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_stru.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOA,&gpio_init_stru);
}

/******************************************************
 * @fun������can���жϿ�����nvic
 * 
 ******************************************************/
void can_nvic_config(){
    NVIC_InitTypeDef nvic_init_struct;

    nvic_init_struct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    nvic_init_struct.NVIC_IRQChannelPreemptionPriority = CAN1_NVIC_IRQPP;
    nvic_init_struct.NVIC_IRQChannelSubPriority = CAN1_NVIC_IRQSP;
    nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_struct);
}

/******************************************************
 * @fun��can����һ������
 * @param��u8  can_id ���ݰ��ı�ʶ��
 *       u8* msg ��������
 *       u8  len �������鳤�ȣ����Ϊ8
 * @return��-1,��ʾ����ʧ��
 *         1 ,��ʾ���ͳɹ�
 ******************************************************/
int can_send_msg(u16 can_id,u8 *msg,u8 len){
    CanTxMsg tx_msg;
    u8 mbox;
    u16 i = 0;

    tx_msg.StdId = can_id;
    tx_msg.IDE = CAN_Id_Standard;   //ʹ�ñ�׼ID
    
    tx_msg.RTR = CAN_RTR_Data;   //��Ϣ����Ϊ����֡
    tx_msg.DLC = len;   //��Ϣ����
    for(i = 0;i < len;i++){
        tx_msg.Data[i] = msg[i];
    }
    mbox = CAN_Transmit(CANX,&tx_msg);  //��ʼ������Ϣ
    i = 0;
    while((CAN_TransmitStatus(CANX,mbox) == CAN_TxStatus_Failed) && (i < 0xfff))i++;
    if(i >= 0xfff) return -1;
    return 1;
}
/******************************************************

*
******************************************************/
CircleQueue *PODOData;

void USB_LP_CAN1_RX0_IRQHandler(void){
   // static char DirFlag = 1;
//    static u8 cnt = 0;
    
    if(CAN_GetITStatus(CANX,CAN_IT_FMP0) != RESET){
        CAN_Receive(CANX,CAN_FIFO0,&g_can_rx_msg);
        CAN_ClearITPendingBit(CANX,CAN_IT_FMP0);
    }
}





