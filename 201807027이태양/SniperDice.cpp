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

void SniperDice::EyeChanged()
{
	AttackCount = 0;
	switch (DiceEye)
	{
	case 1:
		AttackSpeed = 5.0f;
		Power = 100;
		break;
	case 2:
		AttackSpeed = 4.6f;
		Power = 200;
		break;
	case 3:
		AttackSpeed = 4.4f;
		Power = 400;
		break;
	case 4:
		AttackSpeed = 3.8f;
		Power = 800;
		break;
	case 5:
		AttackSpeed = 3.1f;
		Power = 1600;
		break;
	case 6:
		AttackSpeed = 2.0f;
		Power = 3200;
		break;
	default:
		break;
	}
}