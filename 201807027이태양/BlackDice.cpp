#include "BlackDice.h"

BlackDice::BlackDice(int slot, int eye) : DiceBase::DiceBase(slot,eye)
{
	AttackSpeed = 1.0f;
	Color = RGB(0, 0, 0);
	Power = 15;

	DiceType = DICETYPE::BLACK;
	AttackCount = 0;
	AttackType = ATKTYPE::FRONT;
	ShotSpeed = 1.0f;
}
