
#pragma once
#include <vector>
#include <list>
#include "framework.h"
#include "ButtonObject.h" 
#include <memory>

using namespace std;

class DiceBase;
class MonsterBase;
class GameHandler
{

private:
	POINT MousePos;								// ���콺 ��ǥ

	HPEN oldPen;																			
	HBRUSH oldBrush;

	vector<ButtonObject> v_ButtonArr;
	vector<shared_ptr<DiceBase>> v_DiceArr;
	list<shared_ptr<MonsterBase>> l_MonsterArr;	// �߰����� �����ϱ� ���� ����Ʈ ���

	ButtonObject Purchase;						// �ֻ��� ���Ź�ư

	unique_ptr<DiceBase> DraggingDice;			// �ֻ����� �巡���Ҷ� �ӽ÷� �����Ǵ� ��ü
	DiceBase* DraggedDice;						// �巡�� �Ǿ��� ��ü�� �ּҸ� �ӽ÷� ������
	BOOL bDragging;								// ���� �巡�������� ���������� ���� ����. TRUE �ε��� DraggedDice != nullptr �����ؾ���

	int DiceCount;								// ���� ���̽� ����. ���Կ� ������� �ִ��� üũ�ϱ� ���� ���
	HANDLE IDRHandle;
public:
	GameHandler(HWND hWnd);
	~GameHandler();

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawFrame(HDC hdc);

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);
	void ClearDCColor(HDC hdc);

	void OnMouseClicked(int x, int y);


	BOOL IsDragging() const;
	void OnMouseMoved();
	void OnMouseReleased(int x, int y);

	
};
