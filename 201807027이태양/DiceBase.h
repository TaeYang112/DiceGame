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
	int DiceEye;		// 주사위 눈 ( 1 ~ 6 )
	COLORREF Color;		// 테두리 색
	POINT Location;		// 위치
	BOOL IsSelected;
	int DiceType;		// 다이스 종류

public:
	DiceBase(int slot, int eye = 1);
	DiceBase(DiceBase& Dice);

	void DrawDice(HWND hWnd, HDC hdc);
	void SetSlot(int slot);
	void AddEye(int eye);
	bool IsOverlappedPoint(const int x, const int y) const;
	void SetSelected(BOOL IsSelected);
	void ReDraw(HWND hWnd);
	void MoveToMouse(HWND hWnd, POINT point);
	int GetEye();
	BOOL operator==(const DiceBase& Dice2);
};

