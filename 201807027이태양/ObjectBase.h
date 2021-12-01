#pragma once
#include "framework.h"

using namespace std;
enum class DEBUFF
{
	NONE,
	SLOW
};
typedef struct Debuff_
{
	DEBUFF Debuff;
	int Level;
	float Duration;
}Debuff;
class ObjectBase
{
protected:
	POINT Location;
public:
	virtual void DrawObject(HDC hdc) = 0;
	ObjectBase();
	POINT GetLocation() const;
};

