#pragma once
#include "framework.h"
class MonsterBase
{
private:
	int HP;
	int Speed;
	int MoveDir;
	POINT Location;
	static HFONT Font;

public:
	MonsterBase(int HP);
	void DrawMonster(HWND hWnd, HDC hdc);
	BOOL MoveNextPoint();
};

