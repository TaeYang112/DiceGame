#include "MonsterBase.h"

HFONT MonsterBase::Font = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
MonsterBase::MonsterBase(int HP)
{
	this->HP = HP;
	Speed = 2;
	MoveDir = 0;
	Location = {23,388};	// ���� ���� ��ġ
	Status = STATE::ALIVE;
}


void MonsterBase::DrawObject(HDC hdc)
{
	
	const int x = Location.x;
	const int y = Location.y;
	
	HFONT OldFont = (HFONT)SelectObject(hdc, Font);
	HPEN OldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

	COLORREF OldPen_Color = SetDCPenColor(hdc, RGB(175,175,175));
	COLORREF OldBrush_Color = SetDCBrushColor(hdc, RGB(175,175,175));
	COLORREF OldFontColor = SetTextColor(hdc, RGB(255, 255,255));
	


	// �ٱ� �׵θ�
	RoundRect(hdc, x, y, x + 64, y + 64,20,20);

	// ���� ���� �簢��
	SetDCPenColor(hdc, RGB(26, 26, 26));
	SetDCBrushColor(hdc, RGB(26, 26, 26));
	RoundRect(hdc, x+3 , y +3, x + 61, y + 61, 20, 20);

	// ü��ǥ��
	WCHAR HPText[50] = {};
	wsprintf(HPText, TEXT("%d"), HP);
	RECT rect = { x,y,x + 64, y + 64 };
	DrawText(hdc, HPText, -1, &rect,   DT_SINGLELINE|DT_CENTER | DT_VCENTER);
	//TextOut(hdc, x, y + 32, HPText,lstrlenW(HPText));
	

	//����
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SetTextColor(hdc, OldFontColor);

	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
	SelectObject(hdc, OldFont);
	
}

BOOL MonsterBase::MoveNextPoint()
{
	switch (MoveDir)
	{
	case 0:
		Location.y -= Speed;
		if (Location.y <= 88)
			MoveDir = 1;
		break;

	case 1:
		Location.x += Speed;
		if (Location.x >= 623)
			MoveDir = 2;
		break;

	case 2:
		Location.y += Speed;
		if (Location.y >= 388)
			MoveDir = 3;
		break;
	default:
		return TRUE;
		break;
	}
	return FALSE;
}



STATE MonsterBase::GetState() const
{
	return Status;
}

void MonsterBase::SetState(STATE newStatus)
{
	Status = newStatus;
}

BOOL MonsterBase::IsOverlappedPoint(const POINT TargetPoint) const
{

	const int cur_x = Location.x;
	const int cur_y = Location.y;

	if (Location.x <= TargetPoint.x && Location.x + 64 >= TargetPoint.x)	// �ֻ��� �簢�� �ȿ� TargetPoint�� �ִ��� �˻�
	{
		if (Location.y <= TargetPoint.y && Location.y + 64 >= TargetPoint.y)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void MonsterBase::TakeDamage(int Power)
{
	HP -= Power;
	if (HP <= 0)
	{
		HP = 0;
		SetState(STATE::DEAD);
	}
	return;
}