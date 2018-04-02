#include "fun.h"
#include <stdio.h>
int main(){
	int FLAG = 1,cho;
	//初始化程序
	IniProgram();
	while(FLAG){
		Menu();
		scanf("%d",&cho);
		system("cls");
		switch (cho){
			//0.退出
			case 0: FLAG = 0;
			break;
			//1.客房信息设置
			case 1:{
				int FLAG_1=1;
				while(FLAG_1){
					Menu_1();
					scanf("%d",&cho);
					system("cls");
					switch (cho){
						//0.返回
						case 0:	FLAG_1=0;
							break;
						//1.设置客房种类
						case 1:	
							InputType();
							WriteType();
							SetType();
							SaveType();
							break;
						//2.设置层数,房间数
						case 2: 
							InputRoom();
							WriteFloor();
							WriteRoom(0);
							SaveFloor();
							break;
						//3.修改客房信息
						case 3:
							EditInfo();
							SaveRoom();
							break;
						default:
							break;
					}
				}
			}
				break;
			//2.入住登记
			case 2:
				Sign();
				SaveRoom();
				break;
			//3.退房结算
			case 3:
				Cancellation();
				SaveRoom();
				break;
			//4.浏览全部客房的信息
			case 4:
				ShowAllInfo();
				break;
			//5.查询空房间
			case 5:
				ShowByFree();
				break;
			//6.通过房间号查找房间信息
			case 6:
				ShowByNum();
				break;
			//7.按姓名查询房间信息
			case 7:
				ShowByName();
				break;
			default:
				break;
		}
	}
	SaveType();
	SaveRoom();
	SaveFloor();
	return 0;
}