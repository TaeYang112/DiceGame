#pragma once
#include "framework.h"
#include "ObjectBase.h"
class MonsterBase : public ObjectBase
{
private:
	int HP;
	int Speed;
	int MoveDir;
	static HFONT Font;
	BOOL bDead;

public:
	MonsterBase(int HP);
	void DrawObject(HDC hdc);
	BOOL MoveNextPoint();
	BOOL IsDead() const;
	void  SetDead();
};

