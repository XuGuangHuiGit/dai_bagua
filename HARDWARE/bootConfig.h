#ifndef __BOOTCONFIG__H
#define __BOOTCONFIG__H
/**
    @note ʹ��bootloader����������
        ����ͷ�ļ����빤�̣�����  stm32f10x.h  �м������´��룺
                #ifdef IAP
                #include "bootConfig.h"
                #endif
        ��cmd.h ,cmd.c ���빤�̡�������cmd_init()��
        cmd.c ʵ�����Ǵ��ڽ�����ָ��ϵͳ��������Ĭ������˳�������ʱʹ�õ�ָ��û�Ҳ����������ָ���Ӧ�ñ���ԭ�д��롣ʹ�÷�����cmd.h ����
        
                
        �޸Ĺ������ã�option->target->IROM1-> [ start:0x08005000; size:0xC800 ],������ֵӦ������ĺ�ADDR_BEGIN_APP_CFG��APP_SIZE_CFG����һ�¡�
        �޸Ĺ������ã�option->C/C++ ->Define  ����[,IAP] ,ע��ֻ������������ݣ����Ų���ʡ��
        

*/


/* �����������ʹ�õĴ��� */
#define BOOT_USART_CFG 1

/* �������ռ��С */
#define APP_SIZE_CFG        0xC800

/*  ����Ӳ���汾�Ŵ����ַ  */
#define VERSION_ADDR_BASE           0x8004000
#define VERSION_ADDR_OFFEST         0

/* ����app���򴢴���ʼ��ַ
�ú������BootLoader�����㹻�Ĵ���ռ䣬һ������²�Ҫ�޸�
�ú��빤������ͬ���������������޸��ˣ�����ذ������޸ĸú�*/
#define ADDR_BEGIN_APP_CFG	0x08005000

/* ����boot���±�־λ�����ַ��һ�㲻���޸�*/
#define FLAG_FLASH_ADDR_CFG	(ADDR_BEGIN_APP_CFG-0x400)

/* �����������ƫ�� ��ע�⣬��������Ҫ�� ��stm32f10x.h���е����ͷ�ļ�����Ч
* ���� stm32f10x.h �м������´���

                #ifdef IAP
                #include "bootConfig.h"
                #endif
                
*/
#define VECT_TAB_OFFSET_CFG (ADDR_BEGIN_APP_CFG&0x1FFFF)


#endif
