#ifndef __fZ_BLOCK__
#define __fZ_BLOCK__
#include "Box.h"
//class Box;
class BlackBoard;

class fZ_BLOCK:public Box
{
public:
	//const static int BOX_SIZE = 20; 
	
	fZ_BLOCK(int left, int top, int r, int c):Box(left,top,r,c)
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
	virtual bool CanChange();
	virtual Box* Change();

	virtual bool LeftTo(int x)
	{
		return Left() + Col() * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return Left() + (Col() + 3) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return Top() + (-Row() - 1) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 6;
	}
	//int Row1() { return _row1; }
	//int Col1() { return _col1; }

private:
	 //int _row1, _col1; 

};

class fZ_BLOCK1:public Box
{
public:
	//const static int BOX_SIZE = 20; 
	
	fZ_BLOCK1(int left, int top, int r, int c):Box(left,top,r,c)
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
	virtual bool CanChange();
	virtual Box* Change();

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
		return Top() + (-Row() - 3) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 7;
	}
	//int Row1() { return _row1; }
	//int Col1() { return _col1; }

private:
	 //int _row1, _col1; 

};


#endif//__fZ_BLOCK__