#ifndef __TIME__H
#define __TIME__H

#include "global.h"

enum SteerGroup{
    groupA = 0x01,
    groupB = 0x02,
    groupC = 0x04
};

enum SteerChannel{
    channel1 = 0x01,
    channel2 = 0x02,
    channel3 = 0x04,
    channel4 = 0x08
};

enum Motor{
    motor11 = 0x01,
    motor12 = 0x02,
    motor21 = 0x04,
    motor22 = 0x08
};


void TIM2_init(int Time_ms);
void SteerInit(u16 group,u16 channel);
void MotorInit(u16 MotorNum);
void setSteer(int group, int channel , int duty, u8 update);
void setMotor(int MotorNum , int Speed);
void setSteerInTime(int group, int channel , int duty , float runTime);
int getGroupBits(int num);
int getChannelBits(int num);



#endif

