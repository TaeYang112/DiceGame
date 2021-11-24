#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
	Location = { 0,0 };
}
POINT ObjectBase::GetLocation() const
{
	return Location;
}