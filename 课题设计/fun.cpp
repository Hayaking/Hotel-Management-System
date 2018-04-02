#include "fun.h"
int FLAG=0;
TYPE * g_Phead_type;	//第一个房间种类
ROOM * g_Phead_room;	//第一个房间
ROOM *pppHead_room;	//真正的头结点
TCHAR ADRESS[MAX_Adr];	//当前目录路径
TCHAR ADRESS_TYPE[MAX_Adr];//'type.ini'路径
TCHAR ADRESS_ROOM[MAX_Adr];//'room.ini'路径
TCHAR ADRESS_FLOOR[MAX_Adr];//'floor.ini'路径
ROOM T_ROOM;
TYPE T_TYPE;
FLOOR T_FLOOR;
void Menu(){
	StatusBar();
	printf("0.退出\n");
	printf("1.客房信息设置\n");
	printf("2.入住登记\n");
	printf("3.退房结算\n");
	printf("4.浏览全部客房的信息\n");
	printf("5.查询空房间\n");
	printf("6.按房间号查询房间信息\n");
	printf("7.按姓名查询房间信息\n\n");
}
void Menu_1(){
	StatusBar();
	printf("0.返回\n");
	printf("1.增加客房种类\n");
	printf("2.设置楼层和房间数\n");
	printf("3.修改客房信息\n\n");
}
void StatusBar(){
	printf("=================================\n");
	printf("%d种房间\n",T_FLOOR.num_type = get_num_section("type.ini"));
	printf("%d层,共%d个房间,%d个空闲房间\n",T_FLOOR.num_floor,T_FLOOR.sum_room,CountRoomFree(g_Phead_room,0));
	printf("=================================\n");
}

void IniProgram(){
	//获取当前路径,生成各ini文件路径
	//读取type.ini,type个数不为0,生成链表
	//读取floor.ini,room个数不为0,生成链表
	setlocale(LC_ALL, ""); //解决tchar乱码问题   
	printf("=================================\n");
	ReadType();
	ReadFloor();
	ReadRoom();
	
}
//一维到二维,a转换存入buf;
void TranArr1_2(TCHAR a[],TCHAR buf[][20]){
	int i=0,j=0;
	for(int k=0;k<1024;k++){
		if(a[k]=='\0')	buf[i++][j]=a[k],j=0;
		else buf[i][j++]=a[k];
	}
}
//输入类型中的个参数
void InputType(){
	printf("名字:");scanf("%ls",T_TYPE.type);
	printf("代码:");scanf("%d",&T_TYPE.code);
	printf("价格(元):");scanf("%d",&T_TYPE.price);
	printf("押金(元):");scanf("%d",&T_TYPE.deposit);
	printf("时间(小时):");scanf("%d",&T_TYPE.time);
}
//写入类型参数到ini文件
void WriteType(){
	Op_ini_type(&T_TYPE);
}
//读取房间种类
void ReadType(){
	int i;
	TCHAR buf[1024],section[1000][20];//存放节
	GetFpath("\\type.ini",ADRESS_TYPE);
	T_FLOOR.num_type = get_num_section("type.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_TYPE);
	TranArr1_2(buf,section);
	if(T_FLOOR.num_type==0){
		printf("房间种类为0,请先设置种类:\n");
		InputType();
		WriteType();
		SetType();
	}else{//加载类型进链表
		printf("加载房间种类中...\t");
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
		printf("加载完毕\n");
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
//程序启动时初始化
void InputRoom(){
	printf("几层楼:");
	scanf("%d",&T_FLOOR.num_floor);
	for(int i=0;i<T_FLOOR.num_floor;i++){
		printf("%d楼有多少房间:",i+1);
		scanf("%d",&T_FLOOR.num_room[i]);
		printf("设置%d楼房间类型代码:",i+1);
		scanf("%d",&T_FLOOR.code_room[i]);
	}
}
void WriteRoom(int flag){
	Op_ini_room(T_FLOOR,&T_ROOM,flag);
}
//读取各个房间信息
void ReadRoom(){
	int i,j,k;
	TCHAR buf[2048],section[1000][20];//存放节
	ROOM *T;
	GetFpath("\\room.ini",ADRESS_ROOM);
	T_FLOOR.sum_room = get_num_section("room.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_ROOM);
	TranArr1_2(buf,section);
	if(T_FLOOR.sum_room==0){
		printf("房间数量为0,请设置房间数:\n");
		InputRoom();
		WriteRoom(0);
		WriteFloor();
		SetRoom();
	}else{
		printf("加载房间信息中...\t");
		for(i=0,k=0;i<T_FLOOR.num_floor;i++){
			for(j=0;j<T_FLOOR.num_room[i];j++){
				T_ROOM.num=GetPrivateProfileInt(section[k++],_T("num"),0,ADRESS_ROOM);
				T_ROOM.code=GetPrivateProfileInt(section[k-1],_T("code"),0,ADRESS_ROOM);
				T_ROOM.free=GetPrivateProfileInt(section[k-1],_T("free"),0,ADRESS_ROOM);
				if(T_ROOM.free){
					GetPrivateProfileString(section[k-1],_T("name"),_T(""),T_ROOM.guest.name,sizeof(T_ROOM.guest.name),ADRESS_ROOM);
					GetPrivateProfileString(section[k-1],_T("id"),_T(""),T_ROOM.guest.id,sizeof(T_ROOM.guest.id),ADRESS_ROOM);
					//读取入住时间
					T_ROOM.guest.check_in_time.tm_year=GetPrivateProfileInt(section[k-1],_T("check_in_year"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_mon=GetPrivateProfileInt(section[k-1],_T("check_in_mon"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_mday=GetPrivateProfileInt(section[k-1],_T("check_in_day"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_hour=GetPrivateProfileInt(section[k-1],_T("check_in_hour"),0,ADRESS_ROOM);
					T_ROOM.guest.check_in_time.tm_min=GetPrivateProfileInt(section[k-1],_T("check_in_min"),0,ADRESS_ROOM);
					//读取应当退房的时间
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
		printf("加载完毕\n");
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
//读取每层楼房间数
void ReadFloor(){
	TCHAR buf[1024],section[1000][20];//存放节
	GetFpath("\\floor.ini",ADRESS_FLOOR);
	T_FLOOR.num_floor = get_num_section("floor.ini");
	GetPrivateProfileSectionNames(buf,sizeof(buf),ADRESS_FLOOR);
	TranArr1_2(buf,section);
	printf("加载楼层房间数...\t");
	for(int i=0;i<T_FLOOR.num_floor;i++)
		T_FLOOR.num_room[i]=GetPrivateProfileInt(section[i],_T("num"),0,ADRESS_FLOOR);
	printf("加载完毕\n");
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
//登记房间
int Sign(){
	int num,day;	//房间号
	ROOM *temproom;	//临时房间结构体
	TYPE *temptype;
	do{
		printf("输入房间号:");
		scanf("%d",&num);
		temproom=IndexRoom(g_Phead_room,num);	//找到目标房间
	}while(temproom==NULL);
	temptype=IndexCode(g_Phead_type,temproom->code);	//找到目标房间种类

	//获取当前(入住)时间
	time_t temptime;
	time(&temptime);
	struct tm *check_in = &(temproom->guest.check_in_time);
	struct tm *check_out= &(temproom->guest.check_out_time);
	*check_in=*localtime(&temptime);
	
	if(temproom->free==0){ 
		printf("\n房间类型:%ls\n",temptype->type);
		printf("房间价格:%d元/%d小时\n",temptype->price,temptype->time);
		printf("押金:%d元\n\n",temptype->deposit);
		printf("姓名:");		
		scanf("%ls",&temproom->guest.name);

		printf("身份证号:");	
		scanf("%ls",&temproom->guest.id);
		printf("入住天数(钟点房输入1):");
		scanf("%d",&day);

		printf("入住时间:%d-%d-%d  %d:%d\n",check_in->tm_year+1900,check_in->tm_mon,check_in->tm_mday,check_in->tm_hour,check_in->tm_min);
		/*printf("入住时间:%s",asctime(check_in));*/
		temptime=mktime(check_in)+temptype->time*3600*day;	//mktime将时间结构体 转换成 time_t的秒 
		*check_out=*localtime(&temptime);		//将time_t的秒 转换成 时间结构体
		printf("截止时间:%d-%d-%d  %d:%d\n",check_out->tm_year+1900,check_out->tm_mon,check_out->tm_mday,check_out->tm_hour,check_out->tm_min);
		/*printf("入住时间:%s",asctime(check_out));*/
		printf("入住时长限制为%d*%d小时\n",day,temptype->time);
		temproom->free=1;
	}
	else printf("%d忙\n",temproom->num);
	return 0;
}
//退房注销
int Cancellation(){
	int num,money; 
	TCHAR id[20];
	TYPE *temptype;
	char cho;
	ROOM *temproom;	//临时房间结构体
	printf("输入房间号:");
	scanf("%d",&num);
	temproom=IndexRoom(g_Phead_room,num);	//找到目标房间
	temptype=IndexCode(g_Phead_type,temproom->code);	//找到目标房间种类
	printf("身份证号:");
	scanf("%ls",id);
	if(!lstrcmpW(id,temproom->guest.id)){
		printf("验证成功");
	}
	printf("是否扣除押金(Y/N):\n");
	getchar();
	scanf("%c",&cho);
	if(cho=='Y' || cho=='y'){
		printf("输入扣除的金额:");
		scanf("%d",&money);
	}else{
		money=0;
		printf("不扣除押金.\n");
	}
	printf("返还押金%d元.\n",temptype->deposit-money);
	temproom->free=0;
	return 0;
}
//浏览全部客房信息
int ShowAllInfo(){
	ROOM *temproom=g_Phead_room;
	while(temproom!=NULL){
		PrintInfo(temproom);
		temproom=temproom->pNext;
	}
	return 0;
}
//展示空房
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
	printf("房间号:");
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
		printf("未找到!\n");
	return 0;
}
int ShowByName(){
	ROOM *temproom=g_Phead_room;
	TCHAR name[20];
	int count=0;
	printf("名字:");
	scanf("%ls",&name);
	while(temproom!=NULL){
		if(!lstrcmpW(name,temproom->guest.name))
			PrintInfo(temproom),count++;
		temproom=temproom->pNext;
	}
	if(count==0){
		printf("未找到!\n");
	}
	return 0;
}
void PrintInfo(ROOM *temproom){
	TYPE *temptype;
	temptype=IndexCode(g_Phead_type,temproom->code);
	printf("房间号:%d\t%ls\t",temproom->num,temptype->type);
	if(temproom->free==0)	printf("空闲\n");
	else{ 
		printf("忙碌\n");
		printf("\t姓名:%ls\t身份证号:%ls\n",temproom->guest.name,temproom->guest.id);
		printf("\t入住时间:%s",asctime(&(const tm)temproom->guest.check_in_time));	//将struct tm结构体转换成字符串输出
		printf("\t截止时间:%s",asctime(&(const tm)temproom->guest.check_out_time));
	}
}
void EditInfo(){
	ROOM *temproom=g_Phead_room;
	int targetnum;
	char ch;
	printf("房间号:");
	scanf("%d",&targetnum);
	while(temproom!=NULL){
		if(temproom->num==targetnum){
			break;
		}
		temproom=temproom->pNext;
	}
	if(temproom!=NULL){
		printf("是否修改房间种类(Y/N):");
		getchar();
			if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
				printf("类型代码:");
				scanf("%d",temproom->code);
			}

		printf("是否修改房间忙碌状态(Y/N):");
		getchar();
			if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
				printf("空闲状态:");
				scanf("%d",temproom->free);
			}
		if(temproom->free=1){
			printf("是否修改宾客姓名(Y/N):");
			getchar();
				if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
					printf("姓名:");
					scanf("%ls",temproom->guest.name);
				}
			printf("是否修改宾客身份证(Y/N):");
			getchar();
				if(scanf("%c",&ch)&&(ch=='Y'||ch=='y')){
					printf("身份证:");
					scanf("%ls",temproom->guest.id);
				}
		}
	}
}

