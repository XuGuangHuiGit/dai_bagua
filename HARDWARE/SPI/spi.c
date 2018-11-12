#include "spi.h"
#include "usart_u.h"

/**
*   SPI2 初始化函数
*
**/
void SPI2_Init(void)
{
    
 	GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2时钟使能 
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    SPI_Cmd(SPI2, DISABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//CPOL =1
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//CPHA = 1
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;		//ADIS通信速率不能超过2M，此处36/64 = 0.625
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
 
	SPI_Cmd(SPI2, ENABLE);
    	
	SPI2_ReadWriteByte(0xff);		 
}   




/**
*   设置SPI传输速度
*   参数为分频系数
*   
*   注意，当采用burst模式时，最小分频系数为64，即SPI速度不可超过1M
*         当采用手动获取寄存器参数是，分频系数不可超过32，SPI速度不能超过2M
**/
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler){
    
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
 	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;
	SPI_Cmd(SPI2,ENABLE); 

} 

/**
*   spi读写函数
*   参数：要写入从机的值
*   返回值：向从机中写入该值时，从机移位寄存器返回的数据
*/
u8 SPI2_ReadWriteByte(u8 TxData){
	
	u8 retry=0;	
        
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){
		retry++;
		if(retry>200){
            uprintf(USART1 , "error while waiting TX Flag\n");
            return 0;
        }
	}			  
	SPI_I2S_SendData(SPI2, TxData);
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){
		retry++;
		if(retry>200){
            uprintf(USART1 , "error while waiting RX Flag\n");
            return 0;
        }
	}	
    
	return SPI_I2S_ReceiveData(SPI2);				    
}

