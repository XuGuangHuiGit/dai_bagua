#ifndef __LIST__H
#define __LIST__H

#include "sys.h"



typedef struct {
	int timeout;
	int time;
	int duty_pre;
	int duty_next;
	void (*funcition)(int group, int channel , int duty);
}SteerStruction;

typedef struct doubleLink{
	SteerStruction data;
	struct doubleLink *next;
}node ,*link_list;


int list_init(link_list link);
int list_getLength(link_list link);
link_list list_location(link_list link , int loc);
int list_append(link_list link, SteerStruction fun);
int list_remove(link_list link , node * item);




   


#endif 


