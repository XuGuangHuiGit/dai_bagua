#ifndef __USART_U_H__
#define __USART_U_H__

#include "sys.h"
#include "global.h"

void Usart_init(USART_TypeDef* USARTx , u32 baud ,FunctionalState NewState);
void uprintf(USART_TypeDef* USARTx, char *fmt, ...);


#endif
