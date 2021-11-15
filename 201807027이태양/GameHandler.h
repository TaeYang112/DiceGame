#pragma once
#include <vector>
#include "framework.h"
#include "ButtonObject.h" 
#include <memory>

using namespace std;

class DiceBase;
class GameHandler
{

private:
	POINT MousePos;								// 마우스 좌표

	HPEN oldPen;																			
	HBRUSH oldBrush;

	vector<ButtonObject> v_ButtonArr;
	vector<shared_ptr<DiceBase>> v_DiceArr;

	ButtonObject Purchase;						// 주사위 구매버튼

	unique_ptr<DiceBase> DraggingDice;			// 주사위를 드래그할때 임시로 생성되는 객체
	DiceBase* DraggedDice;						// 드래그 되었던 객체의 주소를 임시로 저장함
	BOOL bDragging;

public:
	GameHandler();
	~GameHandler();

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawFrame(HWND hWnd, HDC hdc);

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);
	void ClearDCColor(HDC hdc);

	void OnMouseClicked(HWND hWnd, int x, int y);


	BOOL IsDragging() const;
	void OnMouseMoved(HWND hWnd);
	void OnMouseReleased(HWND hWnd, int x, int y);
};