
#pragma once
#include "framework.h"
#include "ObjectBase.h"
#include "MonsterBase.h"

struct POINTF
{
	float x;
	float y;
};
class MonsterBase;
class ProjectileBase :  public ObjectBase
{
protected:
	int Speed;		// 투사체 속도
	COLORREF Color;
	int Power;
public:
	ProjectileBase(POINT Location, int newPower);
	~ProjectileBase() { std::cout << "제거" << std::endl; }
	BOOL MoveToTarget(MonsterBase* Target);
	virtual void DrawObject(HDC hdc);
	int GetPower() const;
	void Disappear();
};
