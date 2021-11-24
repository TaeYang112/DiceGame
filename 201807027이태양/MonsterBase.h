#pragma once
#include "framework.h"
#include "ObjectBase.h"

enum class STATUS {
	ALIVE = 0,	// »ì¾ÆÀÖÀ½
	ARRIVAL,	// µµÂø
	DEAD		// Á×À½
};
class MonsterBase : public ObjectBase
{
private:
	int HP;
	int Speed;
	int MoveDir;
	static HFONT Font;
	STATUS Status;				

public:
	MonsterBase(int HP);
	void DrawObject(HDC hdc);
	BOOL MoveNextPoint();
	STATUS GetStatus() const;
	void  SetStatus(STATUS newStatus);
	BOOL IsOverlappedPoint(const POINT TargetPoint) const;
	STATUS HitByDice(int Power);
};

