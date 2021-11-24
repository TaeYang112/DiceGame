#pragma once
#include "framework.h"
#include "ObjectBase.h"

#define DICE_BOLD 4
#define EYE_BOLD 10
class DiceBase : ObjectBase
{

private:
	int Slot;			// ����
	int Power;			// ������
	float AttackSpeed;	// ���ݼӵ�
	int DiceEye;		// �ֻ��� �� ( 1 ~ 6 )
	COLORREF Color;		// �׵θ� ��
	BOOL IsSelected;
	int DiceType;		// ���̽� ����

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

