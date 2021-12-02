#include "PurpleDIce.h"

PurpleDIce::PurpleDIce(int slot, int eye) : DiceBase(slot,eye)
{
	AttackSpeed = 0.5f;
	Color = RGB(108, 84, 190);
	Power = 10;
	DiceType = DICETYPE::PURPLE;
	AttackType = ATKTYPE::RANDOM;
	ShotSpeed = 1.0f;
}

void PurpleDIce::EyeChanged()
{
	AttackCount = 0;
	switch (DiceEye)
	{
	case 1:
		AttackSpeed = 0.5f;
		ShotSpeed = 1.0f;
		Power = 10;
		break;
	case 2:
		AttackSpeed = 0.5f;
		Power = 20;
		ShotSpeed = 0.9f;
		break;
	case 3:
		AttackSpeed = 0.5f;
		Power = 35;
		ShotSpeed = 0.8f;
		break;
	case 4:
		AttackSpeed = 0.5f;
		Power = 65;
		ShotSpeed = 0.7f;
		break;
	case 5:
		AttackSpeed = 0.5f;
		Power = 120;
		ShotSpeed = 0.6f;
		break;
	case 6:
		AttackSpeed = 0.5f;
		Power = 200;
		ShotSpeed = 0.5f;
		break;
	default:
		break;
	}

}

