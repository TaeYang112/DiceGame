
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
	int Speed;		// ����ü �ӵ�
	COLORREF Color;
	int Power;
public:
	ProjectileBase(POINT Location, int newPower);
	~ProjectileBase() { std::cout << "����" << std::endl; }
	BOOL MoveToTarget(MonsterBase* Target);
	virtual void DrawObject(HDC hdc);
	int GetPower() const;
	void Disappear();
};
