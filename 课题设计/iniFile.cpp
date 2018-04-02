#include "iniFile.h"
extern TCHAR ADRESS_TYPE[MAX_Adr];
extern TCHAR ADRESS_ROOM[MAX_Adr];
extern TCHAR ADRESS_FLOOR[MAX_Adr];
//写入type->ini文件
void Op_ini_type(TYPE *T){
	TCHAR Type[20],Buf[MAX_Buf];
	INI_ARR(Buf,sizeof(Buf)/2);	//初始化Buf数组
	_stprintf(Buf,_T("code=%d\r\ntype=%s\r\nprice=%d\r\ndeposit=%d\r\ntime=%d"),T->code,T->type,T->price,T->deposit,T->time);
	_stprintf(Type,_T("Type%d"),T->code);
	WriteIniSection(Type,Buf,ADRESS_TYPE);	//写ini节
}
//楼,房间,初始flag==0时 为没有房间
void Op_ini_room(FLOOR F,ROOM *T,int FLAG){
	TCHAR Section[20],Buf[MAX_Buf];
	if(FLAG == 0){
		for(int i=0;i<F.num_floor;i++){
			for(int j=0;j<F.num_room[i];j++){
			INI_ARR(Buf,sizeof(Buf)/2);	//初始化Buf数组
			_stprintf(Buf,_T("num=%d\r\ncode=%d\r\nfree=0"),(i+1)*100+j+1,F.code_room[i]);
			_stprintf(Section,_T("Room%d"),(i+1)*100+j+1);
			WriteIniSection(Section,Buf,ADRESS_ROOM);	//写ini节
			}
		}
	}
	else{
		//printf("%d\n",sizeof(Buf)/2);
		INI_ARR(Buf,sizeof(Buf)/2);	//初始化Buf数组
		_stprintf(Buf,_T("num=%d\r\ncode=%d\r\nfree=%d\r\nname=%ls\r\nid=%ls\r\ncheck_in_year=%d\r\ncheck_in_mon=%d\r\ncheck_in_day=%d\r\ncheck_in_hour=%d\r\ncheck_in_min=%d\r\ncheck_out_year=%d\r\ncheck_out_mon=%d\r\ncheck_out_day=%d\r\ncheck_out_hour=%d\r\ncheck_out_min=%d"),T->num,T->code,T->free,T->guest.name,T->guest.id,T->guest.check_in_time.tm_year,T->guest.check_in_time.tm_mon,T->guest.check_in_time.tm_mday,T->guest.check_in_time.tm_hour,T->guest.check_in_time.tm_min,T->guest.check_out_time.tm_year,T->guest.check_out_time.tm_mon,T->guest.check_out_time.tm_mday,T->guest.check_out_time.tm_hour,T->guest.check_out_time.tm_min);
		_stprintf(Section,_T("Room%d"),T->num);
		WriteIniSection(Section,Buf,ADRESS_ROOM);	//写ini节
	}
}
//层数,房间数
void Op_ini_floor(FLOOR *T){
	TCHAR Section[20],Buf[MAX_Buf];
	for(int i=0;i<T->num_floor;i++){
		INI_ARR(Buf,sizeof(Buf)/2);
		_stprintf(Buf,_T("num=%d"),T->num_room[i]);
		_stprintf(Section,_T("Floor%d"),i+1);
		WriteIniSection(Section,Buf,ADRESS_FLOOR);	//写ini节
	}
}
//得到小节数
int get_num_section(char file[20]){ 
	char ch='[';
	int count=0;
	FILE *fp=fopen(file,"r");
	if(fp==NULL)	printf("error\n");
	else{
		while(!feof(fp))
			if(fgetc(fp)==ch)	count++;
		fclose(fp);
		return count;
	}
	return 0;
}