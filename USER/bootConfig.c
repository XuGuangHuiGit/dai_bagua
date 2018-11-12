//#include "bootConfig.h"
//#include "stm32f10x.h"

//u8 update[] = "update";

//#if BOOT_USART_CFG == 1
//void USART1_IRQHandler(void){
//    
//    u8 c_recv;
//    static u8 update_cnt = 0;
//    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET){      
//        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//        c_recv = USART_ReceiveData(USART1);			  //< = '0x5B'  ESC = 0x1B
//#ifdef IAP       		
//        if(update[update_cnt] == c_recv){
//            update_cnt++;
//            if(update_cnt == 6){
//                FLASH_Status FLASHStatus;
//                FLASH_Unlock();  //解锁FLASH，写数据
//                FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
//                FLASHStatus= FLASH_ErasePage(FLAG_FLASH_ADDR_CFG);//页首地址
//                if(FLASHStatus != FLASH_COMPLETE){ 
//                    FLASH_Lock();//上锁
//                    return;   //擦写失败，，退出
//                }
//                FLASH_Lock();
//             
//                __disable_fault_irq();   
//                NVIC_SystemReset();
//            }
//        }else{
//            update_cnt = 0;
//            if(update[update_cnt] == c_recv){
//                update_cnt++;
//            }
//        }
//#endif
//    }
//}

//   

//#endif



