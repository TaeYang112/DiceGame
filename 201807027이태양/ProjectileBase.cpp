

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

	POINT Dist_vec = { TargetLoc.x - Location.x, TargetLoc.y - Location.y };	// Target과 ProjectileBase의 사이 벡터
	POINT Unit_vec;
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target과 Projectie의 거리를 구함

	Unit_vec.x = Dist_vec.x / Distance;									// 단위벡터로 변환
	Unit_vec.y = Dist_vec.y / Distance;

	Location.x = Unit_vec.x * Speed;
	Location.y = Unit_vec.y * Speed;

	BOOL result = Target->IsOverlappedPoint({ Location.x + 1, Location.y + 1 });	//이동한 지점이 타겟과 겹칠경우
	if (result == TRUE)
	{
		 Target->HitByDice(Power);		// 데미지를 준다음 Status를 반환. 만약 DEAD가 되었을경우 언제든지 nullptr이 될 수 있음
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


	//종료
	SetDCBrushColor(hdc, OldBrush_Color);
	SetDCPenColor(hdc, OldPen_Color);
	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);
}