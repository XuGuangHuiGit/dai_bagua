#include "BMI160.h"
#include "spi.h"

#define Set_CSB(x)      x?GPIO_ResetBits(CSB_PORT , CSB_PIN):GPIO_SetBits(CSB_PORT , CSB_PIN)





///**
//    CSB     ->      PB1
//    

//**/
//void BMI160_Init(){
//    
//    
//    //ÓÃÓÚCSBÒý½Å
//    GPIO_InitTypeDef GPIO_InitStructure;
//    
//    SPI2_Init();
//    
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin = CSB_PIN;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(CSB_PORT , &GPIO_InitStructure);
//    
//    
//    
//    
//    
//}



//u8 readReg(u8 reg){
//    Set_CSB(0);
//    SPI2_ReadWriteByte(reg|0x80);
//    //SPI2_ReadWriteByte(0x00);
//    Set_CSB(1);
//}




