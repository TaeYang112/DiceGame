

#include "ProjectileBase.h"
#include "MonsterBase.h"
#include <math.h>

#define SIZE 11
ProjectileBase::ProjectileBase(POINT Location, int newPower)
{
	Speed = 1;
	Color = RGB(0, 0, 0);
	Power = newPower;
	this->Location = Location;
}

BOOL ProjectileBase::MoveToTarget(MonsterBase* Target)
{
	
	POINT TargetLoc = Target->GetLocation();

	POINT Dist_vec = { TargetLoc.x + 32 - Location.x, TargetLoc.y + 32 - Location.y };	// Target과 ProjectileBase의 사이 벡터
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target과 Projectie의 거리를 구함

	POINTF Unit_vec;
	Unit_vec.x = (float)Dist_vec.x / Distance;									// 단위벡터로 변환
	Unit_vec.y = (float)Dist_vec.y / Distance;

	Location.x += (LONG)(Unit_vec.x * 10);
	Location.y += (LONG)(Unit_vec.y * 10);


	BOOL result = Target->IsOverlappedPoint({ Location.x + 1, Location.y + 1 });	//이동한 지점이 타겟과 겹칠경우
	
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


	//종료
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}

int ProjectileBase::GetPower() const
{
	return Power;
}
