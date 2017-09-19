#ifndef __BOX__
#define __BOX__

class BlackBoard; 


class Box
{
public:
	const static int BOX_SIZE = 20; 
	
	Box(int left, int top, int r, int c); 

    void Reset(int r, int c)
	{
		_row = r;
		_col = c;
	}

	virtual void OnDraw(BlackBoard &board); 
	virtual void OnDrawNextfigure(BlackBoard &board); 
	virtual bool HitBoxes();
	virtual void InsertBox();
	virtual bool CanMove(int dx, int dy); 
	virtual void Move(int dx, int dy); 
	virtual bool CanChange(){return true;};
	virtual Box* Change(){return this;};

	virtual bool LeftTo(int x)
	{
		return _left + _col * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return _left + (_col + 1) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return _top + (-_row - 1) * BOX_SIZE + 1 < y; 
	}

	virtual int getID()
	{
		return 0;
	}

	int& Row() { return _row; }
	int& Col() { return _col; }
	int Left() { return _left; }
	int Top() { return _top; }


private:
	int _left, _top; 
	int _row, _col; 

}; 


#endif // #ifndef __BOX__