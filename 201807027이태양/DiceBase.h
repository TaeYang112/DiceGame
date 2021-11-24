#pragma once
#include "framework.h"
#include "ObjectBase.h"

#define DICE_BOLD 4
#define EYE_BOLD 10
class DiceBase : ObjectBase
{

private:
	int Slot;			// 슬롯
	int Power;			// 데미지
	float AttackSpeed;	// 공격속도
	int DiceEye;		// 주사위 눈 ( 1 ~ 6 )
	COLORREF Color;		// 테두리 색
	BOOL IsSelected;
	int DiceType;		// 다이스 종류

public:
	DiceBase(int slot, int eye = 1);
	DiceBase(DiceBase& Dice);

	void DrawObject(HDC hdc);
	void SetSlot(int slot);
	int GetSlot() const;
	void AddEye(int eye);
	bool IsOverlappedPoint(const POINT TargetPoint) const;
	void SetSelected(BOOL IsSelected);
	void ReDraw(HWND hWnd);
	void MoveToMouse(POINT point);
	int GetEye() const;
	BOOL operator==(const DiceBase& Dice2);
};

