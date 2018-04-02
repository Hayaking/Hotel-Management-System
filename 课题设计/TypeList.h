#ifndef TYPELIST_H
#define TYPELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
typedef struct Type{
	int code;	//������
	TCHAR type[20];	//������������
	int price;	//����۸�
	int deposit;	//Ѻ��
	int time;	//ʱ��/Сʱ
	struct Type *pNext;
}TYPE;
TYPE *Create_TypeList(TYPE T);//��������
TYPE *tail(TYPE *pHead);	//����β�ڵ�ָ��
TYPE *appendType(TYPE *pHead,TYPE T);	//������ĩβ׷��Ԫ��,�����±�
TYPE *IndexCode(TYPE *pHead,int code);	//���Ҵ���,���ط�������
#endif // !TYPELIST_H


