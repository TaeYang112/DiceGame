

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

	POINT Dist_vec = { TargetLoc.x - Location.x, TargetLoc.y - Location.y };	// Target�� Projectile�� ���� ����
	POINT Unit_vec;
	int Distance = (int)sqrt(pow(Dist_vec.x, 2) + pow(Dist_vec.y, 2));	// Target�� Projectie�� �Ÿ��� ����
	
	Unit_vec.x = Dist_vec.x / Distance;									// �������ͷ� ��ȯ
	Unit_vec.y = Dist_vec.y / Distance;

	Location.x = Unit_vec.x * Speed;
	Location.y = Unit_vec.y * Speed;

	return FALSE;
}

void Projectile::DrawObject(HDC hdc)
{
}