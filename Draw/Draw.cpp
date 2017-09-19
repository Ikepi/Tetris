// Draw.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "BlackBoard.h"
#include "UIController.h"

// �ṩ��ͼ�����Ķ���
BlackBoard board; 

// �ɺ���
void ReshapeCallback(int width, int height)
{
	board.UpdateWindowSize(width, height); 
}


// ��ʱ���ص����������幦���߼�����UIController����
void TimerCallback(int value)
{
	UIController::handle().OnTimer(value); 

	// GameSpeed��UIController�У������ڿ����Ѷ�
	board.InstallTimerCallback(UIController::handle().GameSpeed(), TimerCallback, value); 
}

// �������ڴ�����������Ļص�������ڣ����幦���߼�����UIController����
void KeyboardCallback(unsigned char key, int x, int y)
{
	UIController::handle().OnKey(key, x, y); 
}

// �������ڻ��ƵĻص�������ڣ����幦���߼�����UIController����
void DisplayCallback()
{
	board.Clear(); 

	UIController::handle().OnDraw(board); 
	
	board.Flush(); 
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ���´������ڳ�ʼ�����ڵȡ��ɺ���
	board.InitCommandLine(&argc, (char **)argv); 
	board.InitWindowSize(600, 600); 

	board.InitDisplayCallback(DisplayCallback); 
	board.InitKeyboardCallback(KeyboardCallback); 
	board.InitReshapeCallback(ReshapeCallback); 

	board.InstallTimerCallback(UIController::handle().GameSpeed(), TimerCallback, 0);  

	board.Show(); 

	return 0;
}
