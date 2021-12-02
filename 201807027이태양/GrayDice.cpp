#include "GrayDice.h"

GrayDice::GrayDice(int slot, int eye) : DiceBase(slot,eye)
{
	AttackSpeed = 2.0f;
	Color = RGB(150, 150, 150);
	Power = 50;
	DiceType = DICETYPE::GRAY;
	AttackType = ATKTYPE::BACK;
	ShotSpeed = 0.5f;
}

void GrayDice::EyeChanged()
{
	AttackCount = 0;
	switch (DiceEye)
	{
	case 1:
		AttackSpeed = 2.0f;
		Power = 50;
		ShotSpeed = 0.5f;
		break;
	case 2:
		AttackSpeed = 1.9f;
		Power = 100;
		ShotSpeed = 0.6f;
		break;
	case 3:
		AttackSpeed = 1.7f;
		Power = 150;
		ShotSpeed = 0.7f;
		break;
	case 4:
		AttackSpeed = 1.5f;
		Power = 200;
		ShotSpeed = 0.8f;
		break;
	case 5:
		AttackSpeed = 1.3f;
		Power = 250;
		ShotSpeed = 0.9f;
		break;
	case 6:
		AttackSpeed = 1.0f;
		Power = 300;
		ShotSpeed = 1.0f;
		break;
	default:
		break;
	}

}
