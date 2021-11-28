#include "ButtonObject.h"




ButtonObject::ButtonObject(POINT Location, int width, int height)
{
	this->Location = Location;
	Location2.x = Location.x + width;
	Location2.y = Location.y + height;

	ClickFunction = [](){};		// 람다함수 초기화
	DrawFunction = [](HDC hdc){};
	bCircle = FALSE;
}


void ButtonObject::SetClickAction(function<void()> ClickFunction)
{
	this->ClickFunction = ClickFunction;
}

void ButtonObject::OnClickedObject()
{
	
	ClickFunction();
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

	if (Location.x <= x && Location2.x >= x)
	{
		if (Location.y <= y && Location2.y >= y)
		{
			return true;
		}
	}
	return false;
}

