#ifndef INIFILE_H
#define INIFILE_H
#include "windows.h"
#include "RoomList.h"
#include "TypeList.h"
#include <tchar.h>
#include <stdio.h>
#define MAX_Buf 512		//写出ini流最大长度
#define MAX_Adr 100		//地址最大长度
#define MAX_room 99		//最大房间数
#define MAX_floor 10		//最大楼层数
#define WriteIniSection(Section,String,Adress) WritePrivateProfileSection(Section,String,Adress)//写入节
#define INI_ARR(A,size) {for(int iii=0;iii<size;iii++) A[iii]='\0';	}//初始化,避免乱码,我真机智
typedef struct _floor{
	int sum_room;	//总房间数
	int num_floor;	//层数
	int num_type;	//种类数
	int num_room[MAX_room];	//房间数
	int code_room[MAX_floor];	//房间类型代码
}FLOOR;
void Op_ini_type(TYPE *T);	
void Op_ini_room(FLOOR F,ROOM *T,int FLAG);
void Op_ini_floor(FLOOR *T);
int get_num_section(char file[20]);	//通过搜索'['获取ini文件的小节数
#endif // !INIFILE_H

