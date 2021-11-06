#pragma once
#include "framework.h"

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

	HPEN oldPen;																			
	HPEN newPen;
	HBRUSH oldBrush;
	HBRUSH newBrush;

	bool bUsingBrushPen;

public:
	GameHandler();

	Point GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawFrame(HWND hWnd, HDC hdc);

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);
	void ClearDCColor(HDC hdc);
};