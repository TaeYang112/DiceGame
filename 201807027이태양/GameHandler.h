#pragma once
#include <vector>
#include "framework.h"
#include "ButtonObject.h" 

using namespace std;
enum {
	
};

struct Point
{
	int x;
	int y;
};
class GameHandler
{

private:
	Point MousePos;								// ¸¶¿ì½º ÁÂÇ¥
	
	HWND hWnd;

	HPEN oldPen;																			
	HPEN newPen;
	HBRUSH oldBrush;
	HBRUSH newBrush;

	vector<ButtonObject> v_ButtonArr;

	ButtonObject Purchase;

public:
	GameHandler();

	Point GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawFrame(HWND hWnd, HDC hdc);

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);
	void ClearDCColor(HDC hdc);

	void OnClickEvent(HWND hWnd,int x, int y);

	bool flag = false;
};