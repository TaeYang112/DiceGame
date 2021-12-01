

#include "ProjectileBase.h"
#include "MonsterBase.h"
#include <math.h>

#define SIZE 10
ProjectileBase::ProjectileBase(POINT Location, int newPower, COLORREF Color)
{
	Speed = 1;
	this->Color = Color;
	Power = newPower;
	this->Location = Location;
}

BOOL ProjectileBase::MoveToTarget(MonsterBase* Target)
{
	
	POINT TargetLoc = Target->GetLocation();

	POINT Dist_vec = { TargetLoc.x + 32 - Location.x, TargetLoc.y + 32 - Location.y };	// Target�� ProjectileBase�� ���� ����
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target�� Projectie�� �Ÿ��� ����

	POINTF Unit_vec;
	Unit_vec.x = (float)Dist_vec.x / Distance;									// �������ͷ� ��ȯ
	Unit_vec.y = (float)Dist_vec.y / Distance;

	Location.x += (LONG)(Unit_vec.x * 10);
	Location.y += (LONG)(Unit_vec.y * 10);


	BOOL result = Target->IsOverlappedPoint({ Location.x + 1, Location.y + 1 });	//�̵��� ������ Ÿ�ٰ� ��ĥ���
	
	if (result == TRUE)
	{
		 return TRUE;
	}
	
	return FALSE;
}

void ProjectileBase::DrawObject(HDC hdc)
{
	HPEN OldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
	COLORREF OldPen_Color = SetDCPenColor(hdc, Color);
	COLORREF OldBrush_Color = SetDCBrushColor(hdc, Color);


	const int x = Location.x;
	const int y = Location.y;
	


	Ellipse(hdc, x, y, x + SIZE, y + SIZE);


	//����
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}

int ProjectileBase::GetPower() const
{
	return Power;
}


void ProjectileBase::Disappear()		// Projectile�� ��������� õõ�� �����
{
	
	int r_offs = (150 - GetRValue(Color)) / 5;
	
	int g_offs = (150 - GetGValue(Color)) / 5;
	
	int b_offs = (150 - GetBValue(Color)) / 5;

	for (int i = 0; i < 5; i++)
	{
		int r = GetRValue(Color) + r_offs;
		int g = GetGValue(Color) + g_offs;
		int b = GetBValue(Color) + b_offs;
		Color = RGB(r, g, b);
		Sleep(50);
	}
}