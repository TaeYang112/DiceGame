#include "PurpleDIce.h"

PurpleDIce::PurpleDIce(int slot, int eye) : DiceBase(slot,eye)
{
	AttackSpeed = 0.5f;
	Color = RGB(108, 84, 190);
	Power = 10;
	DiceType = DICETYPE::PURPLE;
	AttackType = ATKTYPE::RANDOM;
}


