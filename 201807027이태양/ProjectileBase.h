
#pragma once
#include "framework.h"
#include "ObjectBase.h"
#include "MonsterBase.h"
class MonsterBase;
class ProjectileBase :  public ObjectBase
{
protected:
	int Speed;		// 투사체 속도
	COLORREF Color;
	int Power;
public:
	ProjectileBase(int newPower);
	BOOL MoveToTarget(MonsterBase* Target);
	virtual void DrawObject(HDC hdc);
};
