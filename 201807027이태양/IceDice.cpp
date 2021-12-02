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

void IceDice::EyeChanged()
{
	AttackCount = 0;
	switch (DiceEye)
	{
	case 1:
		AttackSpeed = 1.3f;
		ShotSpeed = 1;
		Power = 10;
		EffDuration = 500;
		AttackType = ATKTYPE::FRONT;
		break;
	case 2:
		AttackSpeed = 1.2f;
		ShotSpeed = 0.9f;
		Power = 20;
		EffDuration = 700;
		AttackType = ATKTYPE::FRONT;
		break;
	case 3:
		AttackSpeed = 1.0f;
		Power = 30;
		ShotSpeed = 0.8f;
		EffDuration = 900;
		AttackType = ATKTYPE::FRONT;
		break;
	case 4:
		AttackSpeed = 0.8f;
		Power = 40;
		ShotSpeed = 0.7f;
		EffDuration = 1100;
		AttackType = ATKTYPE::RANDOM;
		break;
	case 5:
		AttackSpeed = 0.6f;
		Power = 50;
		ShotSpeed = 0.6f;
		EffDuration = 1300;
		AttackType = ATKTYPE::RANDOM;
		break;
	case 6:
		AttackSpeed = 0.4f;
		Power = 60;
		ShotSpeed = 0.5f;
		EffDuration = 1500;
		AttackType = ATKTYPE::RANDOM;
		break;
	default:
		break;
	}

}