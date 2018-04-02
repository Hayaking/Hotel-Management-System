#ifndef TYPELIST_H
#define TYPELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
typedef struct Type{
	int code;	//种类编号
	TCHAR type[20];	//房间种类名字
	int price;	//房间价格
	int deposit;	//押金
	int time;	//时间/小时
	struct Type *pNext;
}TYPE;
TYPE *Create_TypeList(TYPE T);//创造链表
TYPE *tail(TYPE *pHead);	//返回尾节点指针
TYPE *appendType(TYPE *pHead,TYPE T);	//向链表末尾追加元素,返回下标
TYPE *IndexCode(TYPE *pHead,int code);	//查找代码,返回房间类型
#endif // !TYPELIST_H


