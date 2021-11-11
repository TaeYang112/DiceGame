#pragma once
#include <vector>
#include "framework.h"
#include "ButtonObject.h" 
#include "DiceBase.h"

using namespace std;

class DiceBase;
class GameHandler
{

private:
	POINT MousePos;								// ¸¶¿ì½º ÁÂÇ¥
	
	HWND hWnd;

	HPEN oldPen;																			
	HPEN newPen;
	HBRUSH oldBrush;
	HBRUSH newBrush;

	vector<ButtonObject> v_ButtonArr;
	vector<DiceBase*> v_DiceArr;
	ButtonObject Purchase;

public:
	GameHandler();

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawFrame(HWND hWnd, HDC hdc);

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);
	void ClearDCColor(HDC hdc);

	void OnClickEvent(HWND hWnd,int x, int y);

	bool flag = false;
};