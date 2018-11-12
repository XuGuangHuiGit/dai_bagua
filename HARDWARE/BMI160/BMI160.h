#include "sys.h"


#define NV_CONF  0x70
#define ACC_CONF 0x40 
#define ACC_FS	 0x41
#define GRY_CONF 0x42
#define GRY_FS	 0x43
#define PMU_TRIG 0x6c
#define CMD  	 0x7e


#define PMU_STATUS          0x03    //请在这里开启磁力计或者gyro ang accl
#define MAG_CONFIG          0x44    //设置磁力计输出频率，125/2^(7-V),低三位有效
#define MAG_IF_0            0x4B    //set I2c address
#define MAG_IF_1            0x4C    //
#define MAG_IF_2            0x4D    //read regiser
#define MAG_IF_3            0x4E    //reg of write
#define MAG_IF_4            0x4F    //data to write


//定义使用功能引脚
#define CSB_PIN             GPIO_Pin_1
#define CSB_PORT            GPIOB



//void BNI160_Init();


