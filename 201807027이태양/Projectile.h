
#pragma once
#include "framework.h"
#include "ObjectBase.h"
class MonsterBase;
class Projectile :  public ObjectBase
{
protected:
	int Speed;
public:
	Projectile();
	BOOL MoveToTarget(MonsterBase* Target);
	virtual void DrawObject(HDC hdc);
};
