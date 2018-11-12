#ifndef __BOOTCONFIG__H
#define __BOOTCONFIG__H
/**
    @note 使用bootloader升级程序步骤
        将该头文件加入工程，并在  stm32f10x.h  中加入以下代码：
                #ifdef IAP
                #include "bootConfig.h"
                #endif
        将cmd.h ,cmd.c 加入工程。并调用cmd_init()；
        cmd.c 实质上是串口交互的指令系统，在其中默认添加了程序升级时使用的指令，用户也可增加其他指令，但应该保护原有代码。使用方法在cmd.h 中有
        
                
        修改工程配置：option->target->IROM1-> [ start:0x08005000; size:0xC800 ],此两个值应与下面的宏ADDR_BEGIN_APP_CFG和APP_SIZE_CFG保持一致。
        修改工程配置：option->C/C++ ->Define  加入[,IAP] ,注意只有括号里的内容，逗号不可省略
        

*/


/* 定义程序升级使用的串口 */
#define BOOT_USART_CFG 1

/* 定义程序空间大小 */
#define APP_SIZE_CFG        0xC800

/*  定义硬件版本号储存地址  */
#define VERSION_ADDR_BASE           0x8004000
#define VERSION_ADDR_OFFEST         0

/* 定义app程序储存起始地址
该宏给出了BootLoader程序足够的储存空间，一般情况下不要修改
该宏与工程配置同步，若工程配置修改了，则务必按配置修改该宏*/
#define ADDR_BEGIN_APP_CFG	0x08005000

/* 定义boot更新标志位储存地址，一般不用修改*/
#define FLAG_FLASH_ADDR_CFG	(ADDR_BEGIN_APP_CFG-0x400)

/* 定义程序启动偏移 ，注意，该配置需要在 ‘stm32f10x.h’中导入该头文件才有效
* 可在 stm32f10x.h 中加入以下代码

                #ifdef IAP
                #include "bootConfig.h"
                #endif
                
*/
#define VECT_TAB_OFFSET_CFG (ADDR_BEGIN_APP_CFG&0x1FFFF)


#endif
