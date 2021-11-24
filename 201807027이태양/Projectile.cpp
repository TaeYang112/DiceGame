

#include "Projectile.h"
#include "MonsterBase.h"
#include <math.h>

Projectile::Projectile()
{
	Speed = 1;
}

BOOL Projectile::MoveToTarget(MonsterBase* Target)
{

	if (Target == nullptr) return FALSE;
	POINT TargetLoc = Target->GetLocation();

	POINT Dist_vec = { TargetLoc.x - Location.x, TargetLoc.y - Location.y };	// Target과 Projectile의 사이 벡터
	POINT Unit_vec;
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target과 Projectie의 거리를 구함
	
	Unit_vec.x = Dist_vec.x / Distance;									// 단위벡터로 변환
	Unit_vec.y = Dist_vec.y / Distance;

	Location.x = Unit_vec.x * Speed;
	Location.y = Unit_vec.y * Speed;

	return FALSE;
}

void Projectile::DrawObject(HDC hdc)
{
}