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
1.�޸Ĳ�����ʽ
2.�Ż�Ƶ��
v3.0
1.�ع�����
2.ͬ���ǹ���� 
3.�޸�����ͬʱ���Ĵ������� 
v3.1
1.�������,����ϵͳ�ӳ�����
2.���������޵�ʱ��  
3.���԰����м���ʱ
v4.0
1.�������ִ���ṹ�ı�
2.��ϵͳ�ж�Ϊʱ�䵥λ 
3.Ƶ���޸�,���ݷ��÷����ٶ�����
4.���Ӹ񵲸��ٹ��� 
5.����Shift�󰴼������޷���⵽Shift������
v4.1
1.����ini��
2.�޸�����
v5.0beta
1.����killaura
2.���ӳ�����shift���� 
v5.0beta1
1.�Ľ�killaura
v5.0
1.ɾ��killaura
2.���������Ż� 
3.ͳһʱ��ϵͳ
4.�޸ı����� 
v5.1
1.����ʹ��λ�ɸ�
2.�Ż��� 
3.���ƶ������
v5.1rel
1.ini�Ѻû�
2.Ŀ��Ϊ������ˮƽ��Աս�������ɱ¾�⻷���з������� 
3.�İ�������Ϊascii 
v6.0
1.�Ĳ�����ʽ(�����趨ʽ������)
2.���Ӹ�ʱ�䳤������
3.�޸�Ĭ�ϼ��
4.��ʶ�����빥���ٶȵ�ì��
5.�����޵�֡���Ȳ���ini�б�ע�� (���޵�֡��̽��)
v6.0rel
1.���ݻ���ͥʵ��ĸ񵲻��Ƶ������ 
2.�Ļ�˫�������õĲ�����ʽ 
3.�ĸ񵲼��Ϊ�˻����� 
4.�ļ�λ 
v6.1
1.�Ĺ����Ӹ񵲵Ĺ��� (�Ը񵲶Թ�������Ч��Ӱ���̽��) ��ʱ�䳤 
2.�Ķ��µļ�λ 
3.���²�����ʽ(˫shift������) 
4.������д�뿪����־ 
5.ini������ALT��ascii 
6.�ٴ��޸�ʱ�䳤
*/
