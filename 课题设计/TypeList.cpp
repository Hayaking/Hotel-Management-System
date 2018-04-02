#include "TypeList.h"
//��������(С��,��ַ)
TYPE *Create_TypeList(TYPE T){  
    TYPE *pHead = (TYPE *)malloc(sizeof(TYPE));//����һ��ͷ�ڵ�  
    if(pHead == NULL)	printf("�ڴ�����ʧ��\n"),exit(-1);  
    else{   
		TYPE *pTail = pHead;	//β�ڵ�ָ��ͷ
        pHead-> pNext = NULL;	//ͷ�����һ�ڵ�Ϊ�� 
        TYPE *p = (TYPE*)malloc(sizeof(TYPE));  
        if(p == NULL)	printf("�ڴ�����ʧ��\n"),exit(-1);  
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