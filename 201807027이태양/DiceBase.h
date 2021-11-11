#pragma once
#include "framework.h"

#define DICE_BOLD 4
#define EYE_BOLD 10
class DiceBase
{

private:
	int Slot;			// 슬롯
	int Power;			// 데미지
	float AttackSpeed;	// 공격속도
	int DiceEye;			// 주사위 눈 ( 1 ~ 6 )
	COLORREF Color;		// 테두리 색
	POINT Location;		// 위치
	

public:
	void DrawDice(HWND hWnd, HDC hdc);
	void SetSlot(int slot);
	void SetEye(int eye);
	DiceBase(int slot);
};

