#ifndef INIFILE_H
#define INIFILE_H
#include "windows.h"
#include "RoomList.h"
#include "TypeList.h"
#include <tchar.h>
#include <stdio.h>
#define MAX_Buf 512		//д��ini����󳤶�
#define MAX_Adr 100		//��ַ��󳤶�
#define MAX_room 99		//��󷿼���
#define MAX_floor 10		//���¥����
#define WriteIniSection(Section,String,Adress) WritePrivateProfileSection(Section,String,Adress)//д���
#define INI_ARR(A,size) {for(int iii=0;iii<size;iii++) A[iii]='\0';	}//��ʼ��,��������,�������
typedef struct _floor{
	int sum_room;	//�ܷ�����
	int num_floor;	//����
	int num_type;	//������
	int num_room[MAX_room];	//������
	int code_room[MAX_floor];	//�������ʹ���
}FLOOR;
void Op_ini_type(TYPE *T);	
void Op_ini_room(FLOOR F,ROOM *T,int FLAG);
void Op_ini_floor(FLOOR *T);
int get_num_section(char file[20]);	//ͨ������'['��ȡini�ļ���С����
#endif // !INIFILE_H

