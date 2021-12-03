 #include "MonsterBase.h"
#include <math.h>
MonsterBase::MonsterBase(int HP) : SlowDebuff{ 0, }
{
	this->HP = HP;
	Speed = 17;
	MoveDir = 0;
	Location = {23,388};	// 몬스터 스폰 위치
	Status = STATE::ALIVE;
	
	Font = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
}

MonsterBase::~MonsterBase()
{
	DeleteObject(Font);
}

void MonsterBase::DrawObject(HDC hdc)
{
	
	const int x = Location.x;
	const int y = Location.y;
	
	HFONT OldFont = (HFONT)SelectObject(hdc, Font);
	HPEN OldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

	int SlowLv = 0;
	for (int i = 0; i < 6; i++)
	{
		int dur = SlowDebuff[i];
		if (dur > 0) SlowLv = i + 1;
	}
	int b = min(26 + 30*SlowLv,255);

	COLORREF OldPen_Color = SetDCPenColor(hdc, RGB(175,175,175));
	COLORREF OldBrush_Color = SetDCBrushColor(hdc, RGB(175,175,175));
	COLORREF OldFontColor = SetTextColor(hdc, RGB(255, 255,255));
	



	// 바깥 테두리
	RoundRect(hdc, x, y, x + 64, y + 64,20,20);

	// 안쪽 검은 사각형
	SetDCPenColor(hdc, RGB(26, 26, 26));
	SetDCBrushColor(hdc, RGB(26, 26, b));
	RoundRect(hdc, x+3 , y +3, x + 61, y + 61, 20, 20);

	// 체력표시
	WCHAR HPText[5] = {};
	wsprintf(HPText, TEXT("%d"), HP);
	RECT rect = { x,y,x + 64, y + 64 };
	DrawText(hdc, HPText, -1, &rect,   DT_SINGLELINE|DT_CENTER | DT_VCENTER);
	//TextOut(hdc, x, y + 32, HPText,lstrlenW(HPText));
	

	//종료
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SetTextColor(hdc, OldFontColor);

	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
	SelectObject(hdc, OldFont);
	
}

BOOL MonsterBase::MoveNextPoint()
{
	int SleepTime = GetSleepTime();
	for (int i = 0; i < 6; i++)
	{
		int dur = SlowDebuff[i];
		SlowDebuff[i] = dur - SleepTime > 0 ? dur - SleepTime : 0;
	}

	switch (MoveDir)
	{
	case 0:
		Location.y -= 2;
		if (Location.y <= 88)
			MoveDir = 1;
		break;

	case 1:
		Location.x += 2;
		if (Location.x >= 623)
			MoveDir = 2;
		break;

	case 2:
		Location.y += 2;
		if (Location.y >= 388)
			MoveDir = 3;
		break;
	default:
		return TRUE;
		break;
	}
	return FALSE;
}

int MonsterBase::GetSleepTime() 
{
	int SlowLv = 0;
	for (int i = 0; i < 6; i++)
	{
		int dur = SlowDebuff[i];
		if (dur > 0) SlowLv = i + 1;
	}
	float curSpeed = 17 + (20 * SlowLv);
	return curSpeed;
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

	if (Location.x <= TargetPoint.x && Location.x + 64 >= TargetPoint.x)	// 주사위 사각형 안에 TargetPoint가 있는지 검사
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
	cout << "[받은 데미지] " << Power << endl;
	if (HP <= 0)
	{
		HP = 0;
		SetState(STATE::DEAD);
	}
	return;
}

void MonsterBase::SetDebuff(Debuff newDebuff)
{
	switch (newDebuff.Debuff)
	{
	case DEBUFF::SLOW:
		SlowDebuff[newDebuff.Level - 1] += newDebuff.Duration;
		break;
	default:
		break;
	}
}