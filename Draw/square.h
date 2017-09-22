#ifndef __SQUARE__
#define __SQUARE__
#include"Box.h"
//class Box;
class BlackBoard;

class Square:public Box
{
public:
	//const static int BOX_SIZE = 20; 
	
	Square(int left, int top, int r, int c):Box(left,top,r,c)
	{
		//_row1 = Row() - BOX_SIZE + 1;
		//_col1 = Col() + BOX_SIZE - 1;
	}

	//virtual void Reset(int r, int c)
//	{
//		_row1 = r;
//		_col1 = c;
//	}
	virtual bool HitBoxes();
	virtual void OnDraw(BlackBoard &board); 
	virtual void OnDrawNextfigure(BlackBoard &board); 
	virtual bool CanMove(int dx, int dy); 
	virtual void Move(int dx, int dy); 
	virtual void InsertBox();
	virtual bool LeftTo(int x)
	{
		return Left() + Col() * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return Left() + (Col() + 2) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return Top() + (-Row() - 2) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 1;
	}
	//int Row1() { return _row1; }
	//int Col1() { return _col1; }

private:
	 //int _row1, _col1; 

};

#endif//__SQUARE__