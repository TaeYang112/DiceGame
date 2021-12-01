#include "SniperDice.h"

SniperDice::SniperDice(int slot, int eye) : DiceBase(slot, eye)
{
	AttackSpeed = 5.0f;
	ShotSpeed = 3.0f;
	Color = RGB(255, 140, 55);
	Power = 100;
	DiceType = DICETYPE::SNIPER;
	AttackType = ATKTYPE::FRONT;
}
