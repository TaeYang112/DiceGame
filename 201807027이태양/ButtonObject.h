#pragma once
#include "framework.h"
#include <functional>

using namespace std;

class ButtonObject
{
public:
	ButtonObject();

	void SetBounds(int x1, int y1, int x2, int y2);

	void SetClickAction(function<void(HWND hWnd)> ClickFunction);

	void OnClickedObject(HWND hWnd);

	void SetDrawAtion(function<void(HDC hdc)> DrawFunction);

	void DrawObject(HDC hdc);

	bool IsOverlappedPoint(int x, int y);
private:
	int x1, x2;
	int y1, y2;

	function<void(HWND hWnd)> ClickFunction;

	function<void(HDC hdc)> DrawFunction;

};

