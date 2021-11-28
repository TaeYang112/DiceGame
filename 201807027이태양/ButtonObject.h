#pragma once
#include "framework.h"
#include <functional>
#include "ObjectBase.h"

using namespace std;

class ButtonObject : ObjectBase
{
public:
	ButtonObject(POINT Location, int width,int height);

	void SetClickAction(function<void()> ClickFunction);

	void OnClickedObject();

	void SetDrawAtion(function<void(HDC hdc)> DrawFunction);

	void DrawObject(HDC hdc);

	bool IsOverlappedPoint(int x, int y);
private:

	POINT Location2;

	function<void()> ClickFunction;

	function<void(HDC hdc)> DrawFunction;

	BOOL bCircle;
};

