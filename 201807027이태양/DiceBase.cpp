#include "DiceBase.h"
#include "GameHandler.h"


DiceBase::DiceBase(int slot)
{
	AttackSpeed = 1.0f;


	Color = RGB(0, 0, 0);
	DiceEye = 1;
	Location = { 0,0 };
	Power = 0;
	Slot = 1;

	SetSlot(slot);
}

void DiceBase::DrawDice(HWND hWnd, HDC hdc)
{
	//HPEN newPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));	//���� ���� ������ ���� �� ����
	//HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

	//  �� ����
	COLORREF o_PenColor = SetDCPenColor(hdc, Color);
	COLORREF o_BrushColor = SetDCBrushColor(hdc, Color);	


	// �׵θ� ���� ( ������ �ϸ� ũ�� ������ ���� )
	const int x = Location.x;
	const int y = Location.y;
	RoundRect(hdc, x, y, x + 70, y + 70, 20, 20);			


	// �ֻ��� ���� ( ��� )
	SetDCPenColor(hdc, RGB(255,255,255));
	SetDCBrushColor(hdc, RGB(255,255,255));
	RoundRect(hdc, x + DICE_BOLD, y + DICE_BOLD, x + 70 - DICE_BOLD, y + 70 - DICE_BOLD, 20, 20);



	SetDCPenColor(hdc, Color);
	SetDCBrushColor(hdc, Color);
	switch (DiceEye)
	{
	case 1:
		Ellipse(hdc, x + (70 - EYE_BOLD)/ 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2);
		break;
	case 2:
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		break;
	case 3:
		Ellipse(hdc, x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		break;
	case 4:
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		break;
	case 5:
		Ellipse(hdc, x + (70 - EYE_BOLD) / 2, y + (70 - EYE_BOLD) / 2, x + (70 + EYE_BOLD) / 2, y + (70 + EYE_BOLD) / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		break;
	case 6:
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 35 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 35 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 35 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 35 + EYE_BOLD / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		Ellipse(hdc, x + 20 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 20 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 20 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 20 + EYE_BOLD / 2);
		Ellipse(hdc, x + 50 - EYE_BOLD / 2, y + 50 - EYE_BOLD / 2, x + 50 + EYE_BOLD / 2, y + 50 + EYE_BOLD / 2);
		break;
	defulat:
		break;
	}

	



	//����
	//SelectObject(hdc, oldPen);
	//DeleteObject(newPen);
	SetDCBrushColor(hdc, o_BrushColor);
	SetDCPenColor(hdc, o_PenColor);
}



void DiceBase::SetSlot(int slot)
{
	int y = 188 + 72 * ((slot - 1) / 5);
	int x = 155 + 83 * ((slot - 1) % 5);	// �ֻ��� ���� ��ġ ���ϱ�

	Location = { x,y };
	this->Slot = slot;
}

void DiceBase::SetEye(int eye)
{
	DiceEye = eye;
}