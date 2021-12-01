#include "GrayDice.h"

GrayDice::GrayDice(int slot, int eye) : DiceBase(slot,eye)
{
	AttackSpeed = 2.0f;
	Color = RGB(150, 150, 150);
	Power = 50;
	DiceType = DICETYPE::GRAY;
	AttackType = ATKTYPE::BACK;
	ShotSpeed = 0.5;
}
