#include<conio.h>
#include<windows.h>
#include<winuser.h>
#include<cstdio>
#include<iostream>
#include<cstring>
bool AttH;
int SetKey,ShKey,ShKeyOpt;
int SlpDef,SlpAtt,SlpCon,SlpInCon;
int DefKey,AttKey,ConKey;
const int OptT=1,TU=10;
const int Thr_TSet=1000,Thr_TSetKey=200,Thr_TSh=200;
int TSet,TSetKey,TSh;
POINT P;bool Flag[4];
inline bool Key_Down(char C){
	return (GetAsyncKeyState(C)&0x8000)?1:0;
}
inline void sleep(int slpTime){
	Sleep(slpTime);
	TSet=TSet+slpTime;
	TSetKey=TSetKey+slpTime;
	TSh=TSh+slpTime;
	return;
}
inline void ClDown(bool F){
	if(F)mouse_event(MOUSEEVENTF_LEFTDOWN,P.x,P.y,0,0);
	else mouse_event(MOUSEEVENTF_RIGHTDOWN,P.x,P.y,0,0);
	return;
}
inline void ClUp(bool F){
	if(F)mouse_event(MOUSEEVENTF_LEFTUP,P.x,P.y,0,0);
	else mouse_event(MOUSEEVENTF_RIGHTUP,P.x,P.y,0,0);
	return;
}
inline void Click(int F){
	GetCursorPos(&P);
	switch(F){
		case 0:
			ClDown(!AttH);ClUp(!AttH);
			sleep((SlpDef-OptT-1)*TU);
			break;
		case 1:
			ClDown(AttH);ClUp(AttH);
			sleep((SlpAtt-OptT-1)*TU);
			break;
		case 2:
			ClDown(AttH);ClUp(AttH);
			ClDown(!AttH);
			sleep(SlpInCon*TU);
			ClUp(!AttH);
			sleep((SlpCon-SlpInCon-2*OptT-1)*TU);
			break;
	}
	return;
}
inline void Check(){
	if(Key_Down(SetKey))TSetKey=0;
	if(TSetKey<=Thr_TSetKey&&TSet>=Thr_TSet){
		if(Key_Down(DefKey))Flag[0]=!Flag[0],TSet=0;
		if(Key_Down(AttKey))Flag[1]=!Flag[1],TSet=0;
		if(Key_Down(ConKey))Flag[2]=!Flag[2],TSet=0;
	}
	if(TSh>=Thr_TSh&&Key_Down(ShKey)){
		if(Flag[3])keybd_event(ShKeyOpt,0,KEYEVENTF_KEYUP,0);
		else keybd_event(ShKeyOpt,0,0,0);
		Flag[3]=!Flag[3],TSh=0;
	}
	return;
}
inline int Read(){
	std::string sTmp;int x;
	std::cin>>sTmp>>x;
	return x;
}
inline void Init(){
	freopen("click.ini","r",stdin);
	AttH=Read();SetKey=Read();ShKey=Read();ShKeyOpt=Read();
	SlpDef=Read();SlpAtt=Read();SlpCon=Read();SlpInCon=Read();
	DefKey=Read();AttKey=Read();ConKey=Read();
	fclose(stdin);
	return;
}
void MainProc(){
	while(1){
		Check();
		if(Flag[2]||Key_Down(ConKey))Click(2);
		else if(Flag[1]||Key_Down(AttKey))Click(1);
		else if(Flag[0]||Key_Down(DefKey))Click(0);
		sleep(TU);
	}
	return;
}
int main(){
	Init();
	GetCursorPos(&P);
	MainProc();
	return 0;
}
/*Update Logs
v2.0
1.修改操作方式
2.优化频率
v3.0
1.重构代码
2.同轴机枪理念 
3.修复左右同时按的处理问题 
v3.1
1.调整间隔,增加系统延迟修正
2.忽略生物无敌时间  
3.忽略按键中间延时
v4.0
1.按键部分代码结构改变
2.以系统中断为时间单位 
3.频率修改,依据放置方块速度限制
4.增加格挡高速攻击 
5.改善Shift后按键容易无法检测到Shift的问题
v4.1
1.配置ini化
2.修改数据
v5.0beta
1.初步killaura
2.增加持续按shift功能 
v5.0beta1
1.改进killaura
v5.0
1.删除killaura
2.反反作弊优化 
3.统一时间系统
4.修改变量名 
v5.1
1.重新使键位可改
2.优化格挡 
3.改善读入过程
v5.1rel
1.ini友好化
2.目标为辅助低水平人员战斗和面对杀戮光环能有反抗能力 
3.改按键输入为ascii 
v6.0
1.改操作方式(单键设定式的试验)
2.增加格挡时间长度设置
3.修改默认间隔
4.认识格挡率与攻击速度的矛盾
5.测试无敌帧长度并在ini中标注记 (对无敌帧的探究)
v6.0rel
1.根据花雨庭实测的格挡机制调整间隔 
2.改回双操作并用的操作方式 
3.改格挡间隔为了机动性 
4.改键位 
v6.1
1.改攻击加格挡的过程 (对格挡对攻击的有效的影响的探究) 和时间长 
2.改蹲下的键位 
3.蹲下操作方式(双shift的试验) 
4.将试验写入开发日志 
5.ini中增加ALT键ascii 
6.再次修改时间长
*/
