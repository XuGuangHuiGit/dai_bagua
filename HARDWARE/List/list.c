#include "list.h"
#include "stdlib.h"
#include "stdio.h"



//int list_init(link_list link){
//	link = (link_list)malloc(sizeof(node));
//	if (link == NULL){
//		return -1;
//	}
//	link->next = NULL;
//	return -1;
//}

//int list_getLength(link_list link){
//	node *pnode= link->next;
//	int l = 0;
//	while(pnode != NULL){
//		l++;
//		pnode = pnode->next;
//	}
//	return l;
//}

//link_list list_location(link_list link , int loc){
//	int k = 0;
//	link_list p = link;
//	if(loc<0) return NULL;
//	while(p->next != NULL && k!= loc){
//		k++;
//		p = p->next;
//	}
//	return p;
//}


//int list_append(link_list link, SteerStruction fun){
//	link_list p = list_location(link, list_getLength(link)-1);
//	
//	if (p == NULL){
//		return -1;
//	}
//	
//	node *item = (link_list)malloc(sizeof(node));
//	item->data.funcition = fun.funcition;
//	item->data.timeout = fun.timeout;
//	item->next = NULL;
//	
//	p->next = item;
//	return 1;
//}

//int list_remove(link_list link , node * item){
//	link->next = item->next;
//	free(item->data.funcition);
//	free(item);
//}

