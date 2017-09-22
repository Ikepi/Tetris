#ifndef __UICONTROLLER__
#define __UICONTROLLER__

#include <vector>

class Box;
class BlackBoard; 

class UIController
{
public:
	// �����������ɵķ�������
	const static int ROWS = 30; 
	const static int COLS = 10;
	bool _boxes[ROWS][COLS]; //����һ����Ӧ������
	// ��ʼ����λ��
	const static int INITIAL_COL = COLS / 2; 
	
public:
	// UIController���õ���ģʽ�����������Ψһ
	static UIController &handle()
	{
		static UIController instance; 
		return instance; 
	}

	// �����ٶȣ���λ���룬��ÿX�������һ��
	int GameSpeed() { return 400; }

	// ��ʱ�������߼����˴���Ҫ�������������Զ�����
	void OnTimer(int code); 

	// ��ͼ�߼��������߿���ƣ��������
	void OnDraw(BlackBoard &board); 

	// �����߼�����Ҫ�����û����ҡ�����������Ĳ���
	void OnKey(unsigned char key, int x, int y); 

	// �жϷ����Ƿ�����߽硢�ұ߽硢�±߽硢�����й̶�����
	bool HitLeft(Box &box);
	bool HitRight(Box &box);
	bool HitBottom(Box &box);
	bool HitBoxes(Box &box); 

	~UIController(); 

private:
	UIController(); //����ģʽ������޷�ʹ�ù��캯��
	
	// ɾ����������
	void EraseFullRows();

	// ɾ�������к��Ϸ���������
	void PushRows(int row);

	// ���������߼�
	void MoveBoxLeft(); 
	void MoveBoxRight(); 
	void MoveBoxDown(); 
	void MoveBoxchange();//�ı���״������ֻ����������û�ж���
	// ��������̶�����
	void InsertBox(Box *box);
	//{
	//	_boxes[box->Row()][box->Col()] = true; 
	//}
		
private:
	

	int _left,  _bottom; //���ڹ�����Ϸ��Ĵ�С�����������
	int _right, _top; 

	std::vector<Box*> figure;
	//Box _box;
}; 


#endif // #ifndef __UICONTROLLER__