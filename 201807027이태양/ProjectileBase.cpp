

#include "ProjectileBase.h"
#include "MonsterBase.h"
#include <math.h>

ProjectileBase::ProjectileBase(int newPower)
{
	Speed = 1;
	Color = RGB(0, 0, 0);
	Power = newPower;
}

BOOL ProjectileBase::MoveToTarget(MonsterBase* Target)
{
	POINT TargetLoc = Target->GetLocation();

	POINT Dist_vec = { TargetLoc.x - Location.x, TargetLoc.y - Location.y };	// Target�� ProjectileBase�� ���� ����
	POINT Unit_vec;
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target�� Projectie�� �Ÿ��� ����

	Unit_vec.x = Dist_vec.x / Distance;									// �������ͷ� ��ȯ
	Unit_vec.y = Dist_vec.y / Distance;

	Location.x = Unit_vec.x * Speed;
	Location.y = Unit_vec.y * Speed;

	BOOL result = Target->IsOverlappedPoint({ Location.x + 1, Location.y + 1 });	//�̵��� ������ Ÿ�ٰ� ��ĥ���
	if (result == TRUE)
	{
		 Target->HitByDice(Power);		// �������� �ش��� Status�� ��ȯ. ���� DEAD�� �Ǿ������ �������� nullptr�� �� �� ����
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
	


	Ellipse(hdc, x, y, x + 3, y + 3);


	//����
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}