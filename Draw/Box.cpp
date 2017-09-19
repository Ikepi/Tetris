#include "stdafx.h"

#include "Box.h"
#include "BlackBoard.h"
#include "UIController.h"

Box::Box(int left, int top, int r, int c) : _left(left), _top(top), _row(r), _col(c)
{

}


void Box::OnDraw(BlackBoard &board)
{
	int x1 = _left + _col * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = _top  - _row * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 

	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2); 
	board.DrawLine(x2, y1, x2, y2); 
}

void Box::OnDrawNextfigure(BlackBoard &board)
{
	int _col1 = UIController::handle().INITIAL_COL,_row1 = 0;
	int x1 = _left + (_col1+9) * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = _top  - (_row1+3) * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 

	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2); 
	board.DrawLine(x2, y1, x2, y2); 
}

void Box::Move(int dx, int dy)
{
	_row += dx; 
	_col += dy; 
}

bool Box::CanMove(int dx, int dy)
{
	// ����һ����ʱ������ƶ������ж��ƶ����Ƿ񴥷���������
	Box temp = *this;

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

void Box::InsertBox()
{
	UIController::handle()._boxes[Row()][Col()] = true;
}

bool Box::HitBoxes()
{
	return UIController::handle()._boxes[Row()][Col()];
}
