#include "IceDice.h"

IceDice::IceDice(int slot, int eye) : DiceBase(slot, eye)
{
	AttackSpeed = 1.3f;
	Color = RGB(153, 217, 234);
	Power = 10;
	DiceType = DICETYPE::ICE;
	AttackType = ATKTYPE::FRONT;
	Effect = DEBUFF::SLOW;
	EffDuration = 500;
}
