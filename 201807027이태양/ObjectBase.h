#pragma once
#include "framework.h"

class ObjectBase
{
protected:
	POINT Location;
public:
	virtual void DrawObject(HDC hdc) = 0;
	ObjectBase();
	POINT GetLocation() const;
};

