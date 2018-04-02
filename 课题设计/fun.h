#ifndef FUN_H
#define FUN_H
#include <time.h>
#include <locale.h>  
#include "windows.h"
#include "iniFile.h"
#define FORMAT_ROOM "num:\r\ntype:\r\nprice:\r\ndeposit:\r\nfree:\r\n\tname:\r\n\tid:\r\n\tcheck_in_time:\r\n\tcheck_out_time:\r\n"
#define FORMAT_TYPE "num=%d\r\ntype=%s\r\nprice=%d\r\ndeposit=%d\r\ntime=%d\r\n\r\n"
#define Getpath(Adress) GetCurrentDirectory(MAX_Adr,Adress);	//获取当前路径
#define GetFpath(X,Y) {Getpath(ADRESS);lstrcat(ADRESS,_T(X));lstrcpy(Y,ADRESS);}

void InputType();
void WriteType();
void ReadType();
void SetType();	//设置房间种类,生成type.ini文件
void SaveType();
void InputRoom();
void WriteRoom(int flag);
void ReadRoom();
void SetRoom();
void SaveRoom();
void WriteFloor();
void ReadFloor();
void SaveFloor();
int Sign();
int Cancellation();
int ShowAllInfo();
int ShowByFree();
int ShowByNum();
int ShowByName();
void PrintInfo(ROOM *temproom);
void EditInfo();
void IniProgram();
void TranArr1_2(TCHAR a[],TCHAR buf[][20]);
void Menu();
void Menu_1();
void StatusBar();
#endif // !FUN_H

