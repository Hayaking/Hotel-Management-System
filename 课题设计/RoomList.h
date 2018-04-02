#ifndef ROOMLIST_H
#define ROOMLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
typedef struct room{  
    int num;	//������
	int code;	//��������
	int free;	//����״̬,1æ,0��
	struct{	//����ס��
		TCHAR name[20];//ס������
		TCHAR id[20];	//���֤
		struct tm check_in_time;	//��סʱ��
		struct tm check_out_time;	//�˷�ʱ��
	}guest;
	struct room *pNext;//����һ���ṹ��ָ�룬ָ����һ�θ��뵱ǰ�ڵ�����������ͬ�Ľڵ�  
}ROOM; 
ROOM *Create_RoomList(ROOM T);	//��������
ROOM *appendRoom(ROOM *pHead,ROOM T);	//������ĩβ׷��Ԫ��,�����±�
ROOM *tail(ROOM *pHead);	//����β�ڵ�ָ��
int len(ROOM *pHead);	//ͳ��������,���س���
int removeroom(ROOM *pHead,int value);	//�Ƴ�������ĳ��ֵ�ĵ�һ��ƥ����,�����±�
ROOM *IndexRoom(ROOM *pHead,int value);	//���б����ҳ�ĳ��ֵ��һ��ƥ���������λ��,�����±�
int CountRoomFree(ROOM *pHead,int n);	//ͳ�ƿշ�����
#endif