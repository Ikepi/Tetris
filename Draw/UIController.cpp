#include "stdafx.h"

#include <iostream>
#include <time.h>

#include "UIController.h"
#include "BlackBoard.h"
#include "Box.h"
#include "square.h"
#include "I_BLOCK.h"
#include "Z_BLOCK.h"
#include "~Z_BLOCK.h"
#include "Tu_BLOCK.h"
#include "L_BLOCK.h"
#include "fL_BLOCK.h"

int flag ;
Box* current = NULL;
Box* next = NULL;
bool create_newfigure = true;
extern BlackBoard board; //����һ��ȫ�ֱ���

#if 0
	 0.Box,��Ӧflag:0
     1.���η���,û�б���-flag:1
	 2.ֱ����,��������̬-flag:2,3
	 3.��Z��,��������̬-flag:4,5
	 4.��Z��,��������̬-flag:6,7
	 5.����,��������̬-flag:8,9,10,11
	 6.��L��,��������̬-flag:12,13,14,15
	 7.��L��,��������̬-flag:16,17,18,19

#endif

UIController::UIController() : _left(-(COLS * Box::BOX_SIZE / 2)), _bottom(-ROWS * Box::BOX_SIZE / 2), _right(COLS * Box::BOX_SIZE / 2), _top(ROWS * Box::BOX_SIZE / 2)
{//���밴˳��push_back
	figure.push_back(new Box(_left, _top, 0, INITIAL_COL));//flag0-Box
	figure.push_back(new Square(_left, _top, 0, INITIAL_COL));//1-���η���
	figure.push_back(new I_BLOCK(_left, _top, 0, INITIAL_COL));//2-ֱ����0��
	figure.push_back(new I_BLOCK1(_left, _top, 0, INITIAL_COL));//3-ֱ����1��
	figure.push_back(new Z_BLOCK(_left, _top, 0, INITIAL_COL));//4-��Z��0
	figure.push_back(new Z_BLOCK1(_left, _top, 0, INITIAL_COL));//5-��Z��1
	figure.push_back(new fZ_BLOCK(_left, _top, 0, INITIAL_COL));//6-��Z��0
	figure.push_back(new fZ_BLOCK1(_left, _top, 0, INITIAL_COL));//7-��Z��1
	figure.push_back(new Tu_BLOCK(_left, _top, 0, INITIAL_COL));//8-����0
	figure.push_back(new Tu_BLOCK1(_left, _top, 0, INITIAL_COL));//9-����1
	figure.push_back(new Tu_BLOCK2(_left, _top, 0, INITIAL_COL));//10-����2
	figure.push_back(new Tu_BLOCK3(_left, _top, 0, INITIAL_COL));//11-����3
	figure.push_back(new L_BLOCK(_left, _top, 0, INITIAL_COL));//12-��L��0
	figure.push_back(new L_BLOCK1(_left, _top, 0, INITIAL_COL));//13-��L��1
	figure.push_back(new L_BLOCK2(_left, _top, 0, INITIAL_COL));//14-��L��2
	figure.push_back(new L_BLOCK3(_left, _top, 0, INITIAL_COL));//15-��L��3
	figure.push_back(new fL_BLOCK(_left, _top, 0, INITIAL_COL));//16-��L��0
	figure.push_back(new fL_BLOCK1(_left, _top, 0, INITIAL_COL));//17-��L��1
	figure.push_back(new fL_BLOCK2(_left, _top, 0, INITIAL_COL));//18-��L��2
	figure.push_back(new fL_BLOCK3(_left, _top, 0, INITIAL_COL));//19-��L��3
	
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// ��ʼû�й̶�����
			_boxes[r][c] = false; 
		}
	}
}

UIController::~UIController()//��������
{
	for(auto p : figure)
	{
		delete p;
		p = NULL;
	}
}

void UIController::OnDraw(BlackBoard &board) 
{
	//������Ϸ�Ŀ�򣬿����������
	board.SetColor(1, 0, 1); 
	board.DrawLine(_left,  _top,   _left,  _bottom);
	board.DrawLine(_left,  _top,   _right, _top);
	board.DrawLine(_left,  _bottom,_right, _bottom);
	board.DrawLine(_right, _top,   _right, _bottom);
	//����������һ������Ŀ��
	board.SetColor(1, 1, 0); 
	board.DrawLine(_right+Box::BOX_SIZE-1, _top, _right+Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1);
	board.DrawLine(_right+Box::BOX_SIZE-1, _top, _right+7*Box::BOX_SIZE-1, _top);
	board.DrawLine(_right+Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1,_right+7*Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1);
	board.DrawLine(_right+7*Box::BOX_SIZE-1,_top,_right+7*Box::BOX_SIZE-1,_top-6*Box::BOX_SIZE +1);
	//���ɻ�ķ��飬�Լ�Ԥ����һ������
	if(create_newfigure)
	{
		create_newfigure = false;
		if(next == NULL){
			srand((int)time(0));
			flag = rand()%19+1;//����1~19�������
			next = figure[flag];
			srand((int)time(0));
			flag = rand()%19+1;//����1~19�������
			current = figure[flag];

		}
		else{
			current = next;
			srand((int)time(0));
			flag = rand()%19+1;//����1~19�������
			next = figure[flag];
		}
	}
	//������ķ����Լ���һ����Ҫ���ֵķ���
	board.SetColor(1, 0, 0); 
	current->OnDraw(board);
	next->OnDrawNextfigure(board);
	board.SetColor(0, 1, 1); //�����Ѿ�����ķ���
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			if (_boxes[r][c])
			{
				// ����Box����ƹ̶�����
				Box box(_left, _top, r, c); 
				box.OnDraw(board); 
			}
		}
	}
	for (int c = 0; c < COLS; ++c)
	{
		if (_boxes[0][c])//�����ۻ����������Ϸ�������Զ��˳�
		{
			std::cout<<"game over!see you again!"<<std::endl;
			exit(0);
		}
	}
}


void UIController::OnTimer(int code)
{
	MoveBoxDown(); 
}

void UIController::OnKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		std::cout<<"see you"<<std::endl;
		exit(0);//��q�˳�
		break; 
	case 's':
		MoveBoxDown(); //�����ƶ�����
		break; 
	case 'a':
		MoveBoxLeft(); //�����ƶ�����
		break; 
	case 'd':
		MoveBoxRight(); //�����ƶ�����
		break; 
	case 'w':
		MoveBoxchange();//�ı���״
		break;

	}
}

void UIController::InsertBox(Box *box)// ��������̶�����
{
	box->InsertBox();

	create_newfigure = true;
}

bool UIController::HitLeft(Box &box)
{
	return box.LeftTo(_left); 
}

bool UIController::HitRight(Box &box)
{
	return box.RightTo(_right); 
}

bool UIController::HitBottom(Box &box)
{
	return box.LowerTo(_bottom); 
}

bool UIController::HitBoxes(Box &box)
{
	return box.HitBoxes();
}

void UIController::EraseFullRows()
{
	for (int r = 0; r < ROWS; ++r)
	{
		bool fulled = true; 
		for (int c = 0; c < COLS; ++c)
		{
			if (!_boxes[r][c]) 
			{
				// ����һ��λ���޹̶����飬���������������㣬����
				fulled = false; 
				break; 
			}
		}

		if (fulled)
		{
			PushRows(r); 
		}
	}
}

void UIController::PushRows(int row)
{
	for (int r = row; r > 0; --r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// row��֮�Ϸ�������
			_boxes[r][c] = _boxes[r - 1][c]; 
		}
	}

	for (int c = 0; c < COLS; ++c)
	{
		// ���һ���ÿ�
		_boxes[0][c] = false; 
	}
}

void UIController::MoveBoxLeft()
{
	if (current->CanMove(0, -1))
	{
		current->Move(0, -1); 
		board.Update(); 
	}
}

void UIController::MoveBoxRight()
{
	if (current->CanMove(0, 1))
	{
		current->Move(0, 1); 
		board.Update(); 
	}
}

void UIController::MoveBoxchange()
{
	if (current->CanChange())
	{
		current = current->Change();
		board.Update();
	}
}

void UIController::MoveBoxDown()
{
	if (current->CanMove(1, 0))
	{
		current->Move(1, 0); 
		board.Update(); 
	}
	else
	{
		// �޷����ƣ���˵���·����ϰ����߽��̶����飩�����������̶�������
		InsertBox(current);
		//ִ����InsertBox(p)�����󽫻�������ã���current��ΪNULL
		current->Reset(0, INITIAL_COL); 
		current = NULL;
		// �������
		EraseFullRows(); 

		board.Update();
	}
}

