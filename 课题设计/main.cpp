#include "fun.h"
#include <stdio.h>
int main(){
	int FLAG = 1,cho;
	//��ʼ������
	IniProgram();
	while(FLAG){
		Menu();
		scanf("%d",&cho);
		system("cls");
		switch (cho){
			//0.�˳�
			case 0: FLAG = 0;
			break;
			//1.�ͷ���Ϣ����
			case 1:{
				int FLAG_1=1;
				while(FLAG_1){
					Menu_1();
					scanf("%d",&cho);
					system("cls");
					switch (cho){
						//0.����
						case 0:	FLAG_1=0;
							break;
						//1.���ÿͷ�����
						case 1:	
							InputType();
							WriteType();
							SetType();
							SaveType();
							break;
						//2.���ò���,������
						case 2: 
							InputRoom();
							WriteFloor();
							WriteRoom(0);
							SaveFloor();
							break;
						//3.�޸Ŀͷ���Ϣ
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
			//2.��ס�Ǽ�
			case 2:
				Sign();
				SaveRoom();
				break;
			//3.�˷�����
			case 3:
				Cancellation();
				SaveRoom();
				break;
			//4.���ȫ���ͷ�����Ϣ
			case 4:
				ShowAllInfo();
				break;
			//5.��ѯ�շ���
			case 5:
				ShowByFree();
				break;
			//6.ͨ������Ų��ҷ�����Ϣ
			case 6:
				ShowByNum();
				break;
			//7.��������ѯ������Ϣ
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