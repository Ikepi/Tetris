#include "stdafx.h"

#include"I_BLOCK.h"
#include "BlackBoard.h"
#include "UIController.h"
///////////////////////////////////////////////////////////////////
//竖长直条 class I_BLOCK
//////////////////////////////////////////////////////////////////
void I_BLOCK::OnDraw(BlackBoard &board)
{
	int x1 = Left() + Col() * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = Top()  - Row() * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	int y3 = y2 - BOX_SIZE + 1,y4 = y3 - BOX_SIZE + 1,y5 = y4 - BOX_SIZE + 1;
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2);  
	board.DrawLine(x1, y3, x2, y3); 
	board.DrawLine(x1, y4, x2, y4); 
	board.DrawLine(x1, y5, x2, y5);  
	board.DrawLine(x1, y1, x1, y5); 
	board.DrawLine(x2, y1, x2, y5); 
}

void I_BLOCK::OnDrawNextfigure(BlackBoard &board)
{
	int _col1 = UIController::handle().INITIAL_COL,_row1 = 0;
	int x1 = Left() + (_col1+9) * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = Top()  - (_row1+1) * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	int y3 = y2 - BOX_SIZE + 1,y4 = y3 - BOX_SIZE + 1,y5 = y4 - BOX_SIZE + 1;
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2);  
	board.DrawLine(x1, y3, x2, y3); 
	board.DrawLine(x1, y4, x2, y4); 
	board.DrawLine(x1, y5, x2, y5);  
	board.DrawLine(x1, y1, x1, y5); 
	board.DrawLine(x2, y1, x2, y5); 
}

void I_BLOCK::Move(int dx, int dy)
{
	//_row1 += dx; 
	//_col1 += dy; 
	Row() += dx;
	Col() += dy;
}

Box* I_BLOCK::Change()
{
	return new I_BLOCK1(Left(),Top(),Row()+3,Col());
}

bool I_BLOCK::CanChange()
{
	Box* temp = this;

	temp = Change(); 

	if (UIController::handle().HitLeft(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitRight(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitBottom(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitBoxes(*temp))
	{
		return false; 
	}

	return true; 

}

bool I_BLOCK::CanMove(int dx, int dy)
{
	// 借助一个临时方块的移动，来判断移动后是否触发各种条件
	I_BLOCK temp = *this;

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

void I_BLOCK::InsertBox()
{
	UIController::handle()._boxes[Row()][Col()] = true;
	UIController::handle()._boxes[Row()+1][Col()] = true;
	UIController::handle()._boxes[Row()+2][Col()] = true;
	UIController::handle()._boxes[Row()+3][Col()] = true;
}

bool I_BLOCK::HitBoxes()
{
	return UIController::handle()._boxes[Row()][Col()]||UIController::handle()._boxes[Row()+3][Col()]||UIController::handle()._boxes[Row()+2][Col()]||UIController::handle()._boxes[Row()+1][Col()];
}

///////////////////////////////////////////////////////////////////
//横长直条 class I_BLOCK1
///////////////////////////////////////////////////////////////////

void I_BLOCK1::OnDraw(BlackBoard &board)
{
	int x1 = Left() + Col() * BOX_SIZE, x2 = x1 + BOX_SIZE - 1,x3 = x2 + BOX_SIZE - 1,x4 = x3 + BOX_SIZE - 1,x5 = x4 + BOX_SIZE - 1; 
	int y1 = Top()  - Row() * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	
	board.DrawLine(x1, y1, x5, y1); 
	board.DrawLine(x1, y2, x5, y2); 
	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x2, y1, x2, y2); 
	board.DrawLine(x3, y1, x3, y2);  
	board.DrawLine(x4, y1, x4, y2); 
	board.DrawLine(x5, y1, x5, y2); 
}

void I_BLOCK1::OnDrawNextfigure(BlackBoard &board)
{
	int _col1 = UIController::handle().INITIAL_COL,_row1 = 0;
	int x1 = Left() + (_col1+7) * BOX_SIZE, x2 = x1 + BOX_SIZE - 1,x3 = x2 + BOX_SIZE - 1,x4 = x3 + BOX_SIZE - 1,x5 = x4 + BOX_SIZE - 1; 
	int y1 = Top()  - (_row1+3) * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 
	
	board.DrawLine(x1, y1, x5, y1); 
	board.DrawLine(x1, y2, x5, y2); 
	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x2, y1, x2, y2); 
	board.DrawLine(x3, y1, x3, y2);  
	board.DrawLine(x4, y1, x4, y2); 
	board.DrawLine(x5, y1, x5, y2); 
}

void I_BLOCK1::Move(int dx, int dy)
{
	//_row1 += dx; 
	//_col1 += dy; 
	Row() += dx;
	Col() += dy;
}

Box* I_BLOCK1::Change()
{
	return new I_BLOCK(Left(),Top(),Row()-3,Col());//转换式先放着
}

bool I_BLOCK1::CanChange()
{
	Box* temp = this;

	temp = Change(); 

	if (UIController::handle().HitLeft(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitRight(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitBottom(*temp))
	{
		return false; 
	}

	if (UIController::handle().HitBoxes(*temp))
	{
		return false; 
	}

	return true; 
}

bool I_BLOCK1::CanMove(int dx, int dy)
{
	// 借助一个临时方块的移动，来判断移动后是否触发各种条件
	I_BLOCK1 temp = *this;

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

void I_BLOCK1::InsertBox()
{
	UIController::handle()._boxes[Row()][Col()] = true;
	UIController::handle()._boxes[Row()][Col()+1] = true;
	UIController::handle()._boxes[Row()][Col()+2] = true;
	UIController::handle()._boxes[Row()][Col()+3] = true;
}

bool I_BLOCK1::HitBoxes()
{
	return UIController::handle()._boxes[Row()][Col()]||UIController::handle()._boxes[Row()][Col()+1]||UIController::handle()._boxes[Row()][Col()+2]||UIController::handle()._boxes[Row()][Col()+3];
}
