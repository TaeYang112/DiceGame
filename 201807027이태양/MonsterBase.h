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
	static HFONT Font;
	STATE Status;				

public:
	MonsterBase(int HP);

	void DrawObject(HDC hdc);
	BOOL MoveNextPoint();
	STATE GetState() const;
	void  SetState(STATE newStatus);
	BOOL IsOverlappedPoint(const POINT TargetPoint) const;
	void TakeDamage(int Power);
};

