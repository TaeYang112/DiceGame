
#pragma once
#include "framework.h"
#include "ObjectBase.h"


struct POINTF
{
	float x;
	float y;
};
class MonsterBase;
class ProjectileBase :  public ObjectBase
{
protected:
	float Speed;		// 투사체 속도
	COLORREF Color;
	int Power;
	Debuff Effect;
public:
	ProjectileBase(POINT Location, int newPower, float newShotSpeed, COLORREF Color);
	BOOL MoveToTarget(MonsterBase* Target);
	virtual void DrawObject(HDC hdc);
	int GetPower() const;
	void Disappear();
	void SetDebuff(Debuff newDebuff);
	Debuff GetDebuff();
};
