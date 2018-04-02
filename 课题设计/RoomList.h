#ifndef ROOMLIST_H
#define ROOMLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
typedef struct room{  
    int num;	//房间编号
	int code;	//房间种类
	int free;	//空闲状态,1忙,0闲
	struct{	//房间住户
		TCHAR name[20];//住户名字
		TCHAR id[20];	//身份证
		struct tm check_in_time;	//入住时间
		struct tm check_out_time;	//退房时间
	}guest;
	struct room *pNext;//定义一个结构体指针，指向下一次个与当前节点数据类型相同的节点  
}ROOM; 
ROOM *Create_RoomList(ROOM T);	//创造链表
ROOM *appendRoom(ROOM *pHead,ROOM T);	//向链表末尾追加元素,返回下标
ROOM *tail(ROOM *pHead);	//返回尾节点指针
int len(ROOM *pHead);	//统计链表长度,返回长度
int removeroom(ROOM *pHead,int value);	//移除链表中某个值的第一个匹配项,返回下标
ROOM *IndexRoom(ROOM *pHead,int value);	//从列表中找出某个值第一个匹配项的索引位置,返回下标
int CountRoomFree(ROOM *pHead,int n);	//统计空房间数
#endif