#include "stdafx.h"

#include"square.h"
#include "BlackBoard.h"
#include "UIController.h"

void Square::OnDraw(BlackBoard &board)
{
	int x1 = Left() + Col() * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = Top()  - Row() * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	int x3 = x2 + BOX_SIZE - 1,y3 = y2 - BOX_SIZE + 1;
	board.DrawLine(x1, y1, x1, y3); 
	board.DrawLine(x1, y1, x3, y1); 
	board.DrawLine(x1, y3, x3, y3); 
	board.DrawLine(x3, y1, x3, y3); 
	board.DrawLine(x2, y1, x2, y3); 
	board.DrawLine(x1, y2, x3, y2); 
}

void Square::OnDrawNextfigure(BlackBoard &board)
{
	int _col1 = UIController::handle().INITIAL_COL,_row1 = 0;
	int x1 = Left() + (_col1+8) * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = Top()  - (_row1+2) * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	int x3 = x2 + BOX_SIZE - 1,y3 = y2 - BOX_SIZE + 1;
	board.DrawLine(x1, y1, x1, y3); 
	board.DrawLine(x1, y1, x3, y1); 
	board.DrawLine(x1, y3, x3, y3); 
	board.DrawLine(x3, y1, x3, y3); 
	board.DrawLine(x2, y1, x2, y3); 
	board.DrawLine(x1, y2, x3, y2); 
}

void Square::Move(int dx, int dy)
{
	//_row1 += dx; 
	//_col1 += dy; 
	Row() += dx;
	Col() += dy;
}

bool Square::CanMove(int dx, int dy)
{
	// 借助一个临时方块的移动，来判断移动后是否触发各种条件
	Square temp = *this;

	temp.Move(dx, dy); 
	if (UIController::handle().HitLeft(temp))
	{
		return false; 
	}

	if (UIController::handle().HitRight(temp))
	{
		return false; 
	}

	if (UIController::handle().HitBottom(temp))
	{
		return false; 
	}

	if (UIController::handle().HitBoxes(temp))
	{
		return false; 
	}

	return true; 
}

void Square::InsertBox()
{
	UIController::handle()._boxes[Row()][Col()+1] = true;
	UIController::handle()._boxes[Row()+1][Col()] = true;
	UIController::handle()._boxes[Row()+1][Col()+1] = true;
	UIController::handle()._boxes[Row()][Col()] = true;
}

bool Square::HitBoxes()
{
	return UIController::handle()._boxes[Row()+1][Col()]||UIController::handle()._boxes[Row()+1][Col()+1]||UIController::handle()._boxes[Row()][Col()+1]||UIController::handle()._boxes[Row()][Col()];
}