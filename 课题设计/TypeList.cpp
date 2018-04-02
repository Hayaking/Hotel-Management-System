#include "TypeList.h"
//创建链表(小节,地址)
TYPE *Create_TypeList(TYPE T){  
    TYPE *pHead = (TYPE *)malloc(sizeof(TYPE));//分配一个头节点  
    if(pHead == NULL)	printf("内存申请失败\n"),exit(-1);  
    else{   
		TYPE *pTail = pHead;	//尾节点指向头
        pHead-> pNext = NULL;	//头结点下一节点为空 
        TYPE *p = (TYPE*)malloc(sizeof(TYPE));  
        if(p == NULL)	printf("内存申请失败\n"),exit(-1);  
        else{ 
			*p=T;
            pTail-> pNext = p;  
            p-> pNext = NULL;  
            pTail = p;  
        }  
        
    }  
	return pHead->pNext;  
}
TYPE *appendType(TYPE *pHead,TYPE T){
	TYPE *q=(TYPE *)malloc(sizeof(TYPE)),*p = pHead;
	*q=T;
	q->pNext = NULL;
	p = tail(p);
	p->pNext = q;
	return pHead->pNext;
}
TYPE *tail(TYPE *pHead){
	TYPE *p = pHead;
	while(p->pNext != NULL)
		p = p->pNext;
	return p;
}
TYPE *IndexCode(TYPE *pHead,int code){
	TYPE *p=pHead;
	while(p->code!=code){
		p=p->pNext;
	}
	return p;
}