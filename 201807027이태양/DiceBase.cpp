#include "DiceBase.h"
#include "GameHandler.h"
#include "ProjectileBase.h"
#include <iostream>


DiceBase::DiceBase(int slot, int eye)
{
	AttackSpeed = 1.0f;
	Color = RGB(0, 0, 0);
	Location = { 0,0 };
	Power = 15;
	IsSelected = FALSE;
	DiceType = DICETYPE::BLACK;
	bReadyToDel = FALSE;
	
	DiceEye =  eye <= 6 ? eye : 6;
	SetSlot(slot);
	AttackCount = 0;
	AttackType = ATKTYPE::FRONT;
	ShotSpeed = 1.0f;
	Effect = DEBUFF::NONE;
	EffDuration = 0;
}

DiceBase::DiceBase(DiceBase &Dice)
{
	AttackSpeed = Dice.AttackSpeed;


	Color = Dice.Color;
	DiceEye = Dice.DiceEye;
	Location = Dice.Location;
	Power = Dice.Power;
	IsSelected = FALSE;
	DiceType = Dice.DiceType;

	SetSlot(0);
}

DiceBase::~DiceBase()
{
	cout << "[���̽� �Ҹ�]" << endl;
}

BOOL DiceBase::operator==(const DiceBase &Dice2)
{
	if (this->DiceEye == Dice2.DiceEye && this->DiceType == Dice2.DiceType) return TRUE;
	
	return FALSE;
}


void DiceBase::StopTr()
{
	bReadyToDel = TRUE;
}

void DiceBase::DrawObject(HDC hdc)
{
	
	HPEN OldPen =  (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
	COLORREF OldPen_Color = SetDCPenColor(hdc, Color);
	COLORREF OldBrush_Color = SetDCBrushColor(hdc, Color);
	

	COLORREF BColor = (IsSelected == FALSE) ? RGB(255, 255, 255) : RGB(230, 230, 230);	// �巡������ ��ü(����) ��� ȸ��

	// �׵θ� ���� ( ������ �ϸ� ũ�� ������ ���� )
	const int x = Location.x;
	const int y = Location.y;
	RoundRect(hdc, x, y, x + 70, y + 70, 20, 20);			


	// �ֻ��� ���� ( ��� )
	SetDCPenColor(hdc, BColor);
	SetDCBrushColor(hdc, BColor);
	RoundRect(hdc, x + DICE_BOLD, y + DICE_BOLD, x + 70 - DICE_BOLD, y + 70 - DICE_BOLD, 20, 20);


	// �ֻ��� ��
	SetDCPenColor(hdc, Color);
	SetDCBrushColor(hdc, Color);
	
	vector<RECT> v = GetEyeLoc(DiceEye);
	for (auto it = v.begin(); it != v.end(); it++)
	{
		RECT r = *it;
		Ellipse(hdc, r.left, r.top, r.right, r.bottom);
	}



	//����
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}
vector<RECT> DiceBase::GetEyeLoc(int eye)
{
	vector<RECT> v;
	const int x = Location.x;
	const int y = Location.y;
	switch (eye)
	{
	case 1:
		v.push_back({ x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2 });
		break;
	case 2:
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		break;
	case 3:
		v.push_back({ x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2 });
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		break;
	case 4:
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		break;
	case 5:
		
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2 });

		break;
	case 6:
		v.push_back({ x+ 20 - EYE_BOLD / 2, y + 35 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 35 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 35 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 35 + EYE_BOLD / 2 });
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });
		v.push_back({ x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2 });
		v.push_back({ x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2 });

		break;
	default:
		v.push_back({ x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2 });
		break;
	}
	return v;
}


bool DiceBase::IsOverlappedPoint(const POINT TargetPoint) const
{

	const int cur_x = Location.x;
	const int cur_y = Location.y;

	if (Location.x <= TargetPoint.x && Location.x + 70 >= TargetPoint.x)	// �ֻ��� �簢�� �ȿ� TargetPoint�� �ִ��� �˻�
	{
		if (Location.y <= TargetPoint.y && Location.y + 70 >= TargetPoint.y)
		{
			return true;
		}
	}
	return false;
}

void DiceBase::SetSelected(BOOL IsSelected)
{
	this->IsSelected = IsSelected;
}
/*
void DiceBase::ReDraw(HWND hWnd)
{
	const int x = Location.x;
	const int y = Location.y;
	RECT rect = { x,y,x + 70,y + 70 };
	InvalidateRect(hWnd, &rect, FALSE);
}
*/
void DiceBase::MoveToMouse(POINT point)
{
	Location.x = point.x - 35;		// point�� �ֻ��� ���߾��� ���� ��
	Location.y = point.y - 35;

}

int DiceBase::GetEye() const
{
	return DiceEye;
}

void DiceBase::AddEye(int eye)
{
	DiceEye = DiceEye + eye <= 6 ? DiceEye + eye : 6;
	EyeChanged();
}

void DiceBase::EyeChanged()
{
	AttackCount = 0;
	switch (DiceEye)
	{
	case 1:
		AttackSpeed = 1.0f;
		Power = 15;
		ShotSpeed = 1.0f;
		break;
	case 2:
		AttackSpeed = 0.9f;
		Power = 30;
		ShotSpeed = 1.1f;
		break;
	case 3:
		AttackSpeed = 0.8f;
		Power = 45;
		ShotSpeed = 1.2f;
		break;
	case 4:
		AttackSpeed = 0.65f;
		Power = 60;
		ShotSpeed = 1.3f;
		break;
	case 5:
		AttackSpeed = 0.5f;
		Power = 75;
		ShotSpeed = 1.4f;
		break;
	case 6:
		AttackSpeed = 0.3f;
		Power = 90;
		ShotSpeed = 1.5f;
		break;
	default:
		break;
	}
}
void DiceBase::SetSlot(int slot)
{
	int y = 188 + 72 * (slot / 5);
	int x = 155 + 83 * (slot % 5);	// �ֻ��� ���� ��ġ ���ϱ�

	Location = { x,y };
	this->Slot = slot;
}

int DiceBase::GetSlot() const
{
	return Slot;
}

float DiceBase::GetSpeed() const
{
	return AttackSpeed;
}

shared_ptr<ProjectileBase> DiceBase::SpawnProj()
{
	AttackCount++;
	int index = AttackCount % DiceEye;
	RECT LocRect = GetEyeLoc(DiceEye)[index];
	POINT Loc = { LocRect.left, LocRect.top };
	shared_ptr<ProjectileBase> Proj = make_shared<ProjectileBase>(Loc,Power,ShotSpeed,Color);
	Proj->SetDebuff(GetDebuff());

	return Proj;
}

ATKTYPE DiceBase::GetAttackType() const
{
	return AttackType;
}

Debuff DiceBase::GetDebuff()
{
	Debuff reDebuff = { Effect,DiceEye,EffDuration * DiceEye };
	return reDebuff;
}

void DiceBase::SetUpgradNum(int num)
{
	UpgradeNum = num;
}

DICETYPE DiceBase::GetType() const
{
	return DiceType;
}