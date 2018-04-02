#include "fun.h"
int FLAG=0;
TYPE * g_Phead_type;	//��һ����������
ROOM * g_Phead_room;	//��һ������
ROOM *pppHead_room;	//������ͷ���
TCHAR ADRESS[MAX_Adr];	//��ǰĿ¼·��
TCHAR ADRESS_TYPE[MAX_Adr];//'type.ini'·��
TCHAR ADRESS_ROOM[MAX_Adr];//'room.ini'·��
TCHAR ADRESS_FLOOR[MAX_Adr];//'floor.ini'·��
ROOM T_ROOM;
TYPE T_TYPE;
FLOOR T_FLOOR;
void Menu(){
	StatusBar();
	printf("0.�˳�\n");
	printf("1.�ͷ���Ϣ����\n");
	printf("2.��ס�Ǽ�\n");
	printf("3.�˷�����\n");
	printf("4.���ȫ���ͷ�����Ϣ\n");
	printf("5.��ѯ�շ���\n");
	printf("6.������Ų�ѯ������Ϣ\n");
	printf("7.��������ѯ������Ϣ\n\n");
}
void Menu_1(){
	StatusBar();
	printf("0.����\n");
	printf("1.���ӿͷ�����\n");
	printf("2.����¥��ͷ�����\n");
	printf("3.�޸Ŀͷ���Ϣ\n\n");
}
void StatusBar(){
	printf("=================================\n");
	printf("%d�ַ���\n",T_FLOOR.num_type = get_num_section("type.ini"));
	printf("%d��,��%d������,%d�����з���\n",T_FLOOR.num_floor,T_FLOOR.sum_room,CountRoomFree(g_Phead_room,0));
	printf("=================================\n");
}

void IniProgram(){
	//��ȡ��ǰ·��,���ɸ�ini�ļ�·��
	//��ȡtype.ini,type������Ϊ0,��������
	//��ȡfloor.ini,room������Ϊ0,��������
	setlocale(LC_ALL, ""); //���tchar��������   
	printf("=================================\n");
	ReadType();
	ReadFloor();
	ReadRoom();
	
}
//һά����ά,aת������buf;
void TranArr1_2(TCHAR a[],TCHAR buf[][20]){
	int i=0,j=0;
	for(int k=0;k<1024;k++){
		if(a[k]=='\0')	buf[i++][j]=a[k],j=0;
		else buf[i][j++]=a[k];
	}
}
//���������еĸ�����
void InputType(){
	printf("����:");scanf("%ls",T_TYPE.type);
	printf("����:");scanf("%d",&T_TYPE.code);
	printf("�۸�(Ԫ):");scanf("%d",&T_TYPE.price);
	printf("Ѻ��(Ԫ):");scanf("%d",&T_TYPE.deposit);
	printf("ʱ��(Сʱ):");scanf("%d",&T_TYPE.time);
}
//д�����Ͳ�����ini�ļ�
void WriteType(){
	Op_ini_type(&T_TYPE);
}
//��ȡ��������
void ReadType(){
	int i;
	TCHAR buf[1024],section[1000][20];//��Ž�
	GetFpath("\\type.ini",ADRESS_TYPE);
	T_FLOOR.num_type = get_num_section("type.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_TYPE);
	TranArr1_2(buf,section);
	if(T_FLOOR.num_type==0){
		printf("��������Ϊ0,������������:\n");
		InputType();
		WriteType();
		SetType();
	}else{//�������ͽ�����
		printf("���ط���������...\t");
		for(i=0;i<T_FLOOR.num_type;i++){
			T_TYPE.code=GetPrivateProfileInt(section[i],_T("code"),-1,ADRESS_TYPE);
			GetPrivateProfileString(section[i],_T("type"),_T(""),T_TYPE.type,sizeof(T_TYPE),ADRESS_TYPE);
			T_TYPE.price=GetPrivateProfileInt(section[i],_T("price"),-1,ADRESS_TYPE);
			T_TYPE.deposit=GetPrivateProfileInt(section[i],_T("deposit"),-1,ADRESS_TYPE);
			T_TYPE.time=GetPrivateProfileInt(section[i],_T("time"),-1,ADRESS_TYPE);
			SetType();
			FLAG=1;
			T_FLOOR.num_type--;
		}
		printf("�������\n");
		FLAG=0;
	}
}
void SetType(){
	TYPE *T;
	if(T_FLOOR.num_type==0 || FLAG==0){
		T=Create_TypeList(T_TYPE);
		g_Phead_type=T;
		T_FLOOR.num_type++;
	}else{
		T=appendType(g_Phead_type,T_TYPE);
		T_FLOOR.num_type++;
	}
}
//��������ʱ��ʼ��
void InputRoom(){
	printf("����¥:");
	scanf("%d",&T_FLOOR.num_floor);
	for(int i=0;i<T_FLOOR.num_floor;i++){
		printf("%d¥�ж��ٷ���:",i+1);
		scanf("%d",&T_FLOOR.num_room[i]);
		printf("����%d¥�������ʹ���:",i+1);
		scanf("%d",&T_FLOOR.code_room[i]);
	}
}
void WriteRoom(int flag){
	Op_ini_room(T_FLOOR,&T_ROOM,flag);
}
//��ȡ����������Ϣ
void ReadRoom(){
	int i,j,k;
	TCHAR buf[2048],section[1000][20];//��Ž�
	ROOM *T;
	GetFpath("\\room.ini",ADRESS_ROOM);
	T_FLOOR.sum_room = get_num_section("room.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_ROOM);
	TranArr1_2(buf,section);
	if(T_FLOOR.sum_room==0){
		printf("��������Ϊ0,�����÷�����:\n");
		InputRoom();
		WriteRoom(0);
		WriteFloor();
		SetRoom();
	}else{
		printf("���ط�����Ϣ��...\t");
		for(i=0,k=0;i<T_FLOOR.num_floor;i++){
			for(j=0;j<T_FLOOR.num_room[i];j++){
				T_ROOM.num=GetPrivateProfileInt(section[k++],_T("num"),0,ADRESS_ROOM);
				T_ROOM.code=GetPrivateProfileInt(section[k-1],_T("code"),0,ADRESS_ROOM);
				T_ROOM.free=GetPrivateProfileInt(section[k-1],_T("free"),0,ADRESS_ROOM);
				if(T_ROOM.free){
					GetPrivateProfileString(section[k-1],_T("name"),_T(""),T_ROOM.guest.name,sizeof(T_ROOM.guest.name),ADRESS_ROOM);
					GetPrivateProfileString(section[k-1],_T("id"),_T(""),T_ROOM.guest.id,sizeof(T_ROOM.guest.id),ADRESS_ROOM);
					//��ȡ��סʱ��
					T_ROOM.guest.check_in_time.tm_year=GetPrivateProfileInt(section[k-1],_T("check_in_year"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_mon=GetPrivateProfileInt(section[k-1],_T("check_in_mon"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_mday=GetPrivateProfileInt(section[k-1],_T("check_in_day"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_hour=GetPrivateProfileInt(section[k-1],_T("check_in_hour"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_min=GetPrivateProfileInt(section[k-1],_T("check_in_min"),0,ADRESS_ROOM);
					//��ȡӦ���˷���ʱ��
					T_ROOM.guest.check_out_time.tm_year=GetPrivateProfileInt(section[k-1],_T("check_out_year"),0,ADRESS_ROOM);
					T_ROOM.guest.check_out_time.tm_mon=GetPrivateProfileInt(section[k-1],_T("check_out_mon"),0,ADRESS_ROOM);
					T_ROOM.guest.check_out_time.tm_mday=GetPrivateProfileInt(section[k-1],_T("check_out_day"),0,ADRESS_ROOM);
					T_ROOM.guest.check_out_time.tm_hour=GetPrivateProfileInt(section[k-1],_T("check_out_hour"),0,ADRESS_ROOM);
					T_ROOM.guest.check_out_time.tm_min=GetPrivateProfileInt(section[k-1],_T("check_out_min"),0,ADRESS_ROOM);
				}
				else{
					INI_ARR(T_ROOM.guest.id,sizeof(T_ROOM.guest.id)/2);
					INI_ARR(T_ROOM.guest.name,sizeof(T_ROOM.guest.name)/2);
					T_ROOM.guest.check_in_time.tm_year=0;
					T_ROOM.guest.check_in_time.tm_mon=0;
					T_ROOM.guest.check_in_time.tm_mday=0;
					T_ROOM.guest.check_in_time.tm_hour=0;
					T_ROOM.guest.check_in_time.tm_min=0;

					T_ROOM.guest.check_out_time.tm_year=0;
					T_ROOM.guest.check_out_time.tm_mon=0;
					T_ROOM.guest.check_out_time.tm_mday=0;
					T_ROOM.guest.check_out_time.tm_hour=0;
					T_ROOM.guest.check_out_time.tm_min=0;

				}
				if(FLAG==0){
					T=Create_RoomList(T_ROOM);
					g_Phead_room = T;
					FLAG=1;
				}
				else
					T=appendRoom(T,T_ROOM);
			}
		}
		printf("�������\n");
	}
}
void SetRoom(){
	ROOM *T;
	int i=0,j;
	for(i=0;i<T_FLOOR.num_floor;i++){
		for(j=0;j<T_FLOOR.num_room[i];j++){
			if(i==0&&j==0 || FLAG==0){
				T=Create_RoomList(T_ROOM);
				g_Phead_room = T;
				FLAG=1;
			}
			else    T=appendRoom(T,T_ROOM);
		}
		
	}
	FLAG=0;
}
void WriteFloor(){
	Op_ini_floor(&T_FLOOR);
}
//��ȡÿ��¥������
void ReadFloor(){
	TCHAR buf[1024],section[1000][20];//��Ž�
	GetFpath("\\floor.ini",ADRESS_FLOOR);
	T_FLOOR.num_floor = get_num_section("floor.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_FLOOR);
	TranArr1_2(buf,section);
	printf("����¥�㷿����...\t");
	for(int i=0;i<T_FLOOR.num_floor;i++)
		T_FLOOR.num_room[i]=GetPrivateProfileInt(section[i],_T("num"),0,ADRESS_FLOOR);
	printf("�������\n");
}
void SaveType(){
	TYPE *T=g_Phead_type;
	for(int i=0;i<T_FLOOR.num_type;i++){
		Op_ini_type(T);
		T = T->pNext;
	}
}
void SaveRoom(){
	ROOM *T=g_Phead_room;
	for(int i=0;i<T_FLOOR.sum_room;i++){
		Op_ini_room(T_FLOOR,T,1);
		T = T->pNext;
	}
}
void SaveFloor(){
	WriteFloor();
}
//�ǼǷ���
int Sign(){
	int num,day;	//�����
	ROOM *temproom;	//��ʱ����ṹ��
	TYPE *temptype;
	do{
		printf("���뷿���:");
		scanf("%d",&num);
		temproom=IndexRoom(g_Phead_room,num);	//�ҵ�Ŀ�귿��
	}while(temproom==NULL);
	temptype=IndexCode(g_Phead_type,temproom->code);	//�ҵ�Ŀ�귿������

	//��ȡ��ǰ(��ס)ʱ��
	time_t temptime;
	time(&temptime);
	struct tm *check_in = &(temproom->guest.check_in_time);
	struct tm *check_out= &(temproom->guest.check_out_time);
	*check_in=*localtime(&temptime);
	
	if(temproom->free==0){ 
		printf("\n��������:%ls\n",temptype->type);
		printf("����۸�:%dԪ/%dСʱ\n",temptype->price,temptype->time);
		printf("Ѻ��:%dԪ\n\n",temptype->deposit);
		printf("����:");		
		scanf("%ls",&temproom->guest.name);

		printf("���֤��:");	
		scanf("%ls",&temproom->guest.id);
		printf("��ס����(�ӵ㷿����1):");
		scanf("%d",&day);

		printf("��סʱ��:%d-%d-%d  %d:%d\n",check_in->tm_year+1900,check_in->tm_mon,check_in->tm_mday,check_in->tm_hour,check_in->tm_min);
		/*printf("��סʱ��:%s",asctime(check_in));*/
		temptime=mktime(check_in)+temptype->time*3600*day;	//mktime��ʱ��ṹ�� ת���� time_t���� 
		*check_out=*localtime(&temptime);		//��time_t���� ת���� ʱ��ṹ��
		printf("��ֹʱ��:%d-%d-%d  %d:%d\n",check_out->tm_year+1900,check_out->tm_mon,check_out->tm_mday,check_out->tm_hour,check_out->tm_min);
		/*printf("��סʱ��:%s",asctime(check_out));*/
		printf("��סʱ������Ϊ%d*%dСʱ\n",day,temptype->time);
		temproom->free=1;
	}
	else printf("%dæ\n",temproom->num);
	return 0;
}
//�˷�ע��
int Cancellation(){
	int num,money; 
	TCHAR id[20];
	TYPE *temptype;
	char cho;
	ROOM *temproom;	//��ʱ����ṹ��
	printf("���뷿���:");
	scanf("%d",&num);
	temproom=IndexRoom(g_Phead_room,num);	//�ҵ�Ŀ�귿��
	temptype=IndexCode(g_Phead_type,temproom->code);	//�ҵ�Ŀ�귿������
	printf("���֤��:");
	scanf("%ls",id);
	if(!lstrcmpW(id,temproom->guest.id)){
		printf("��֤�ɹ�");
	}
	printf("�Ƿ�۳�Ѻ��(Y/N):\n");
	getchar();
	scanf("%c",&cho);
	if(cho=='Y' || cho=='y'){
		printf("����۳��Ľ��:");
		scanf("%d",&money);
	}else{
		money=0;
		printf("���۳�Ѻ��.\n");
	}
	printf("����Ѻ��%dԪ.\n",temptype->deposit-money);
	temproom->free=0;
	return 0;
}
//���ȫ���ͷ���Ϣ
int ShowAllInfo(){
	ROOM *temproom=g_Phead_room;
	while(temproom!=NULL){
		PrintInfo(temproom);
		temproom=temproom->pNext;
	}
	return 0;
}
//չʾ�շ�
int ShowByFree(){
	ROOM *temproom=g_Phead_room;
	while(temproom!=NULL){
		if(temproom->free==0){
			PrintInfo(temproom);
		}
		temproom=temproom->pNext;
	}
	printf("\n");
	return 0;
}
int ShowByNum(){
	ROOM *temproom=g_Phead_room;
	int targetnum;
	printf("�����:");
	scanf("%d",&targetnum);
	while(temproom!=NULL){
		if(temproom->num==targetnum){
			PrintInfo(temproom);
			break;
		}	
		else
			temproom=temproom->pNext;
	}
	if(temproom==NULL)
		printf("δ�ҵ�!\n");
	return 0;
}
int ShowByName(){
	ROOM *temproom=g_Phead_room;
	TCHAR name[20];
	int count=0;
	printf("����:");
	scanf("%ls",&name);
	while(temproom!=NULL){
		if(!lstrcmpW(name,temproom->guest.name))
			PrintInfo(temproom),count++;
		temproom=temproom->pNext;
	}
	if(count==0){
		printf("δ�ҵ�!\n");
	}
	return 0;
}
void PrintInfo(ROOM *temproom){
	TYPE *temptype;
	temptype=IndexCode(g_Phead_type,temproom->code);
	printf("�����:%d\t%ls\t",temproom->num,temptype->type);
	if(temproom->free==0)	printf("����\n");
	else{ 
		printf("æµ\n");
		printf("\t����:%ls\t���֤��:%ls\n",temproom->guest.name,temproom->guest.id);
		printf("\t��סʱ��:%s",asctime(&(const tm)temproom->guest.check_in_time));	//��struct tm�ṹ��ת�����ַ������
		printf("\t��ֹʱ��:%s",asctime(&(const tm)temproom->guest.check_out_time));
	}
}
void EditInfo(){
	ROOM *temproom=g_Phead_room;
	int targetnum;
	char ch;
	printf("�����:");
	scanf("%d",&targetnum);
	while(temproom!=NULL){
		if(temproom->num==targetnum){
			break;
		}
		temproom=temproom->pNext;
	}
	if(temproom!=NULL){
		printf("�Ƿ��޸ķ�������(Y/N):");
		getchar();
			if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
				printf("���ʹ���:");
				scanf("%d",temproom->code);
			}

		printf("�Ƿ��޸ķ���æµ״̬(Y/N):");
		getchar();
			if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
				printf("����״̬:");
				scanf("%d",temproom->free);
			}
		if(temproom->free=1){
			printf("�Ƿ��޸ı�������(Y/N):");
			getchar();
				if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
					printf("����:");
					scanf("%ls",temproom->guest.name);
				}
			printf("�Ƿ��޸ı������֤(Y/N):");
			getchar();
				if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
					printf("���֤:");
					scanf("%ls",temproom->guest.id);
				}
		}
	}
}

