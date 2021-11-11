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
	//HPEN newPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));	//펜의 굵기 설정을 위해 펜 변경
	//HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

	//  색 변경
	COLORREF o_PenColor = SetDCPenColor(hdc, Color);
	COLORREF o_BrushColor = SetDCBrushColor(hdc, Color);	


	// 테두리 역할 ( 선으로 하면 크기 예상이 힘듬 )
	const int x = Location.x;
	const int y = Location.y;
	RoundRect(hdc, x, y, x + 70, y + 70, 20, 20);			


	// 주사위 안쪽 ( 흰색 )
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

	



	//종료
	//SelectObject(hdc, oldPen);
	//DeleteObject(newPen);
	SetDCBrushColor(hdc, o_BrushColor);
	SetDCPenColor(hdc, o_PenColor);
}



void DiceBase::SetSlot(int slot)
{
	int y = 188 + 72 * ((slot - 1) / 5);
	int x = 155 + 83 * ((slot - 1) % 5);	// 주사위 슬롯 위치 구하기

	Location = { x,y };
	this->Slot = slot;
}

void DiceBase::SetEye(int eye)
{
	DiceEye = eye;
}