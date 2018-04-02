#include "RoomList.h"
extern ROOM *pppHead_room;
ROOM *Create_RoomList(ROOM T){  
	ROOM *pHead = (ROOM *)malloc(sizeof(ROOM));//分配一个头节点
	pppHead_room=pHead;
    if(pHead == NULL)	printf("内存申请失败\n"),exit(-1);  
    else{   
		ROOM *pTail = pHead;	//尾节点指向头
        pHead-> pNext = NULL;	//头结点下一节点为空 
		ROOM *p = (ROOM*)malloc(sizeof(ROOM));  
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
void insert(ROOM *pHead,int pos,int val){
	ROOM *p = pHead;
	int i;
	for(i=0;i<pos-1;i++){
		p = p->pNext;
		if(p->pNext->pNext == NULL)	break;
	}
	ROOM *q=(ROOM*)malloc(sizeof(ROOM));
	//插入位置大于等于实际长度
	if(p->pNext->pNext == NULL){
		q->num = val;
		q->pNext = NULL;
		p->pNext->pNext = q;
	}
	else{
		q->num = val;
		q->pNext = p->pNext;
		p->pNext = q;
	}
}
void pop(ROOM *pHead,int pos){
	ROOM *p = pHead;
	int i;
	for(i=0;i<pos-1;i++){
		p = p->pNext;
		if(p->pNext->pNext==NULL)	break;
	}
	ROOM *temp;
	if(p->pNext->pNext==NULL || pos ==-1)
		free(p->pNext),p->pNext = NULL;
	else{
		temp = p->pNext->pNext;
		free(p->pNext);
		p->pNext = temp;
	}
}
void print(ROOM *pHead){
	ROOM *p = pHead;
	while(p->pNext!=NULL)
		p = p->pNext, printf("%d\t",p->num);
	printf("\n");
}
int len(ROOM *pHead){
	ROOM *p=pHead;
	int len=0;
	while(p->pNext!=NULL)    p = p->pNext, len++;
	return len;
}
int removeroom(ROOM *pHead,int value){
	ROOM *p=pHead,*temp;
	int i;
	for(i=0;i<len(pHead);i++){
		if(value==p->pNext->num){
			temp = p->pNext->pNext;
			free(p->pNext);
			p->pNext = temp;
			break;
		}
		else    p = p->pNext;
	}
	return i;//返回下标
}
ROOM *IndexRoom(ROOM *pHead,int value){
	ROOM *p=pHead;
	int i,Len = len(pHead);
	for(i=0;i<Len;i++)
		if(value==p->num)	break;
		else    p = p->pNext;
	if(i==Len)	return NULL;
	return p;
}
ROOM *appendRoom(ROOM *pHead,ROOM T){
	ROOM *q=(ROOM *)malloc(sizeof(ROOM)),*p = pHead;
	*q=T;
	q->pNext = NULL;
	p = tail(p);
	p->pNext = q;
	return pHead->pNext;
}
ROOM *tail(ROOM *pHead){
	ROOM *p = pHead;
	while(p->pNext != NULL)
		p = p->pNext;
	return p;
}
int CountRoomFree(ROOM *pHead,int n){
	ROOM *p = pHead;
	int c = 0;
	while(p!= NULL){
		if(p->free==n)	c++;
		p = p->pNext;
	}
	return c;
}
