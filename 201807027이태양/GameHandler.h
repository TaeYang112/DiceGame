
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
	POINT MousePos;								// 마우스 좌표

	HPEN oldPen;																			
	HBRUSH oldBrush;

	vector<ButtonObject> v_ButtonArr;
	vector<shared_ptr<DiceBase>> v_DiceArr;
	list<shared_ptr<MonsterBase>> l_MonsterArr;	// 중간에서 삭제하기 위해 리스트 사용

	ButtonObject Purchase;						// 주사위 구매버튼

	unique_ptr<DiceBase> DraggingDice;			// 주사위를 드래그할때 임시로 생성되는 객체
	DiceBase* DraggedDice;						// 드래그 되었던 객체의 주소를 임시로 저장함
	BOOL bDragging;								// 현재 드래그중인지 상태정보를 갖는 변수. TRUE 인동안 DraggedDice != nullptr 보장해야함

	int DiceCount;								// 현재 다이스 개수. 슬롯에 빈공간이 있는지 체크하기 위해 사용
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
