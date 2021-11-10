#include "ButtonObject.h"




ButtonObject::ButtonObject() : x1(0), x2(0), y1(0), y2(0)
{
	ClickFunction = [](HWND hWnd){};		// 람다함수 초기화
	DrawFunction = [](HDC hdc){};
	
}

void ButtonObject::SetBounds(int x1, int y1, int x2, int y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void ButtonObject::SetClickAction(function<void(HWND hWnd)> ClickFunction)
{
	this->ClickFunction = ClickFunction;
}

void ButtonObject::OnClickedObject(HWND hWnd)
{
	
	ClickFunction(hWnd);
}

void ButtonObject::SetDrawAtion(function<void(HDC hdc)> DrawFunction)
{
	this->DrawFunction = DrawFunction;
}

void ButtonObject::DrawObject(HDC hdc)
{
	DrawFunction(hdc);
}

bool ButtonObject::IsOverlappedPoint(int x, int y)
{

	if (x1 <= x && x2 >= x)
	{
		if (y1 <= y && y2 >= y)
		{
			return true;
		}
	}
	return false;
}
