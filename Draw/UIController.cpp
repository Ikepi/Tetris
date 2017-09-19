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
extern BlackBoard board; //声明一个全局变量

#if 0
	 0.Box,对应flag:0
     1.田形方块,没有变形-flag:1
	 2.直长条,有两种形态-flag:2,3
	 3.正Z形,有两种形态-flag:4,5
	 4.反Z形,有两种形态-flag:6,7
	 5.土形,有四种形态-flag:8,9,10,11
	 6.正L形,有四种形态-flag:12,13,14,15
	 7.反L形,有四种形态-flag:16,17,18,19

#endif

UIController::UIController() : _left(-(COLS * Box::BOX_SIZE / 2)), _bottom(-ROWS * Box::BOX_SIZE / 2), _right(COLS * Box::BOX_SIZE / 2), _top(ROWS * Box::BOX_SIZE / 2)
{//必须按顺序push_back
	figure.push_back(new Box(_left, _top, 0, INITIAL_COL));//flag0-Box
	figure.push_back(new Square(_left, _top, 0, INITIAL_COL));//1-田形方块
	figure.push_back(new I_BLOCK(_left, _top, 0, INITIAL_COL));//2-直长条0竖
	figure.push_back(new I_BLOCK1(_left, _top, 0, INITIAL_COL));//3-直长条1横
	figure.push_back(new Z_BLOCK(_left, _top, 0, INITIAL_COL));//4-正Z形0
	figure.push_back(new Z_BLOCK1(_left, _top, 0, INITIAL_COL));//5-正Z形1
	figure.push_back(new fZ_BLOCK(_left, _top, 0, INITIAL_COL));//6-反Z形0
	figure.push_back(new fZ_BLOCK1(_left, _top, 0, INITIAL_COL));//7-反Z形1
	figure.push_back(new Tu_BLOCK(_left, _top, 0, INITIAL_COL));//8-土形0
	figure.push_back(new Tu_BLOCK1(_left, _top, 0, INITIAL_COL));//9-土形1
	figure.push_back(new Tu_BLOCK2(_left, _top, 0, INITIAL_COL));//10-土形2
	figure.push_back(new Tu_BLOCK3(_left, _top, 0, INITIAL_COL));//11-土形3
	figure.push_back(new L_BLOCK(_left, _top, 0, INITIAL_COL));//12-正L形0
	figure.push_back(new L_BLOCK1(_left, _top, 0, INITIAL_COL));//13-正L形1
	figure.push_back(new L_BLOCK2(_left, _top, 0, INITIAL_COL));//14-正L形2
	figure.push_back(new L_BLOCK3(_left, _top, 0, INITIAL_COL));//15-正L形3
	figure.push_back(new fL_BLOCK(_left, _top, 0, INITIAL_COL));//16-反L形0
	figure.push_back(new fL_BLOCK1(_left, _top, 0, INITIAL_COL));//17-反L形1
	figure.push_back(new fL_BLOCK2(_left, _top, 0, INITIAL_COL));//18-反L形2
	figure.push_back(new fL_BLOCK3(_left, _top, 0, INITIAL_COL));//19-反L形3
	
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// 初始没有固定方块
			_boxes[r][c] = false; 
		}
	}
}

UIController::~UIController()//析构函数
{
	for(auto p : figure)
	{
		delete p;
		p = NULL;
	}
}

void UIController::OnDraw(BlackBoard &board) 
{
	//画出游戏的框框，可以灵活设置
	board.SetColor(1, 0, 1); 
	board.DrawLine(_left,  _top,   _left,  _bottom);
	board.DrawLine(_left,  _top,   _right, _top);
	board.DrawLine(_left,  _bottom,_right, _bottom);
	board.DrawLine(_right, _top,   _right, _bottom);
	//画出放置下一个方块的框框
	board.SetColor(1, 1, 0); 
	board.DrawLine(_right+Box::BOX_SIZE-1, _top, _right+Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1);
	board.DrawLine(_right+Box::BOX_SIZE-1, _top, _right+7*Box::BOX_SIZE-1, _top);
	board.DrawLine(_right+Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1,_right+7*Box::BOX_SIZE-1, _top-6*Box::BOX_SIZE +1);
	board.DrawLine(_right+7*Box::BOX_SIZE-1,_top,_right+7*Box::BOX_SIZE-1,_top-6*Box::BOX_SIZE +1);
	//生成活动的方块，以及预报下一个方块
	if(create_newfigure)
	{
		create_newfigure = false;
		if(next == NULL){
			srand((int)time(0));
			flag = rand()%19+1;//产生1~19的随机数
			next = figure[flag];
			srand((int)time(0));
			flag = rand()%19+1;//产生1~19的随机数
			current = figure[flag];

		}
		else{
			current = next;
			srand((int)time(0));
			flag = rand()%19+1;//产生1~19的随机数
			next = figure[flag];
		}
	}
	//画出活动的方块以及下一个将要出现的方块
	board.SetColor(1, 0, 0); 
	current->OnDraw(board);
	next->OnDrawNextfigure(board);
	board.SetColor(0, 1, 1); //画出已经下落的方块
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			if (_boxes[r][c])
			{
				// 借助Box类绘制固定方块
				Box box(_left, _top, r, c); 
				box.OnDraw(board); 
			}
		}
	}
	for (int c = 0; c < COLS; ++c)
	{
		if (_boxes[0][c])//方块累积到框框顶则游戏结束，自动退出
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
		exit(0);//按q退出
		break; 
	case 's':
		MoveBoxDown(); //向下移动方块
		break; 
	case 'a':
		MoveBoxLeft(); //向左移动方块
		break; 
	case 'd':
		MoveBoxRight(); //向右移动方块
		break; 
	case 'w':
		MoveBoxchange();//改变形状
		break;

	}
}

void UIController::InsertBox(Box *box)// 活动方块插入固定方块
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
				// 任意一个位置无固定方块，则满行条件不满足，跳过
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
			// row行之上方块下落
			_boxes[r][c] = _boxes[r - 1][c]; 
		}
	}

	for (int c = 0; c < COLS; ++c)
	{
		// 最顶层一行置空
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
		// 无法下移，则说明下方有障碍（边界或固定方块），则活动方块插入固定方块中
		InsertBox(current);
		//执行完InsertBox(p)操作后将活动方块重置，将current置为NULL
		current->Reset(0, INITIAL_COL); 
		current = NULL;
		// 清楚满行
		EraseFullRows(); 

		board.Update();
	}
}

