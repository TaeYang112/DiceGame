#pragma once
#include "framework.h"
#include "ObjectBase.h"
#include <iostream>
enum class STATE {
	ALIVE,		// »ì¾ÆÀÖÀ½
	ARRIVAL,	// µµÂø
	DEAD		// Á×À½
};
enum class MONSTER {
	ORIGINAL,
};
class MonsterBase : public ObjectBase
{
private:
	int HP;
	int Speed;
	int MoveDir;
	HFONT Font;
	STATE Status;
	int SlowDebuff[6];

public:
	MonsterBase(int HP);
	~MonsterBase();
	void DrawObject(HDC hdc);
	BOOL MoveNextPoint();
	STATE GetState() const;
	void  SetState(STATE newStatus);
	BOOL IsOverlappedPoint(const POINT TargetPoint) const;
	void TakeDamage(int Power);
	void SetDebuff(Debuff newDebuff);
};

