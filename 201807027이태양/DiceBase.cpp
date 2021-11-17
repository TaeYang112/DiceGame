#include "DiceBase.h"
#include "GameHandler.h"


DiceBase::DiceBase(int slot, int eye)
{
	AttackSpeed = 1.0f;
	Color = RGB(0, 0, 0);
	Location = { 0,0 };
	Power = 0;
	IsSelected = FALSE;
	DiceType = 0;

	DiceEye =   eye <= 6 ? eye : 6;
	SetSlot(slot);
	
}

DiceBase::DiceBase(DiceBase &Dice)
{
	AttackSpeed = Dice.AttackSpeed;


	Color = Dice.Color;
	DiceEye = Dice.DiceEye;
	Location = Dice.Location;
	Power = Dice.Power;
	IsSelected = FALSE;
	DiceType = 0;

	SetSlot(0);
}

BOOL DiceBase::operator==(const DiceBase &Dice2)
{
	if (this->DiceEye == Dice2.DiceEye) return TRUE;
	
	return FALSE;
}

void DiceBase::DrawDice(HWND hWnd, HDC hdc)
{
	
	HPEN OldPen =  (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
	COLORREF OldPen_Color = SetDCPenColor(hdc, Color);
	COLORREF OldBrush_Color = SetDCBrushColor(hdc, Color);
	

	COLORREF BColor = (IsSelected == FALSE) ? RGB(255, 255, 255) : RGB(230, 230, 230);	// 드래그중인 객체(원본) 라면 회색

	// 테두리 역할 ( 선으로 하면 크기 예상이 힘듬 )
	const int x = Location.x;
	const int y = Location.y;
	RoundRect(hdc, x, y, x + 70, y + 70, 20, 20);			


	// 주사위 안쪽 ( 흰색 )
	SetDCPenColor(hdc, BColor);
	SetDCBrushColor(hdc, BColor);
	RoundRect(hdc, x + DICE_BOLD, y + DICE_BOLD, x + 70 - DICE_BOLD, y + 70 - DICE_BOLD, 20, 20);


	// 주사위 눈
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
	default:
		break;
	}

	



	//종료
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}




bool DiceBase::IsOverlappedPoint(const int x, const int y) const
{

	const int cur_x = Location.x;
	const int cur_y = Location.y;

	if ( cur_x<= x && cur_x + 70 >= x)
	{
		if (cur_y <= y && cur_y + 70 >= y)
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

void DiceBase::ReDraw(HWND hWnd)
{
	const int x = Location.x;
	const int y = Location.y;
	RECT rect = { x,y,x + 70,y + 70 };
	InvalidateRect(hWnd, &rect, FALSE);
}

void DiceBase::MoveToMouse(HWND hWnd, POINT point)
{
	Location.x = point.x - 35;		// point에 주사위 정중앙이 오게 함
	Location.y = point.y - 35;
	InvalidateRect(hWnd, NULL, FALSE);

}

int DiceBase::GetEye() const
{
	return DiceEye;
}

void DiceBase::AddEye(int eye)
{
	DiceEye = DiceEye + eye <= 6 ? DiceEye + eye : 6;

}
void DiceBase::SetSlot(int slot)
{
	int y = 188 + 72 * (slot / 5);
	int x = 155 + 83 * (slot % 5);	// 주사위 슬롯 위치 구하기

	Location = { x,y };
	this->Slot = slot;
}

int DiceBase::GetSlot() const
{
	return Slot;
}