#ifndef __I_BLOCK__
#define __I_BLOCK__

#include"Box.h"
//class Box;
class BlackBoard;

class I_BLOCK:public Box
{
public:
	I_BLOCK(int left, int top, int r, int c):Box(left,top,r,c)
	{
		//_row1 = Row() - BOX_SIZE + 1;
		//_col1 = Col() + BOX_SIZE - 1;
	}
	virtual bool HitBoxes();
	virtual void OnDraw(BlackBoard &board); 
	virtual void OnDrawNextfigure(BlackBoard &board); 
	virtual bool CanMove(int dx, int dy); 
	virtual void Move(int dx, int dy); 
	virtual void InsertBox();
	virtual bool CanChange();
	virtual Box* Change();

	virtual bool LeftTo(int x)
	{
		return Left() + Col() * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return Left() + (Col() + 1) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return Top() + (-Row() - 4) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 2;
	}
	//int Row1() { return _row1; }
	//int Col1() { return _col1; }

private:
	 //int _row1, _col1; 

};

class I_BLOCK1:public Box
{
public:
	I_BLOCK1(int left, int top, int r, int c):Box(left,top,r,c)
	{
		//_row1 = Row() - BOX_SIZE + 1;
		//_col1 = Col() + BOX_SIZE - 1;
	}
	virtual bool HitBoxes();
	virtual void OnDraw(BlackBoard &board); 
	virtual void OnDrawNextfigure(BlackBoard &board); 
	virtual bool CanMove(int dx, int dy); 
	virtual void Move(int dx, int dy); 
	virtual void InsertBox();
	virtual bool CanChange();
	virtual Box* Change();

	virtual bool LeftTo(int x)
	{
		return Left() + Col() * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return Left() + (Col() + 4) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return Top() + (-Row() - 1) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 3;
	}
	//int Row1() { return _row1; }
	//int Col1() { return _col1; }

private:
	 //int _row1, _col1; 

};

#endif//__I_BLOCK__