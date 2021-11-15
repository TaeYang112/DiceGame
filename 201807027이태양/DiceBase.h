#pragma once
#include "framework.h"

#define DICE_BOLD 4
#define EYE_BOLD 10
class DiceBase
{

private:
	int Slot;			// ����
	int Power;			// ������
	float AttackSpeed;	// ���ݼӵ�
	int DiceEye;		// �ֻ��� �� ( 1 ~ 6 )
	COLORREF Color;		// �׵θ� ��
	POINT Location;		// ��ġ
	BOOL IsSelected;
	int DiceType;		// ���̽� ����

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

