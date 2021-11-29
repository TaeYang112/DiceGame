#pragma once
#include "framework.h"
#include "ObjectBase.h"
#include "ProjectileBase.h"
#include <memory>
#include <vector>

#define DICE_BOLD 4
#define EYE_BOLD 10

using namespace std;
class ProjectileBase;
class DiceBase : ObjectBase
{

private:
	int Slot;			// 슬롯
	int Power;			// 데미지
	float AttackSpeed;	// 공격속도
	int DiceEye;		// 주사위 눈 ( 1 ~ 6 )
	COLORREF Color;		// 테두리 색
	BOOL IsSelected;
	int DiceType;		// 다이스 종류
	BOOL bReadyToDel;
	int AttackCount;	// 공격횟수.  Projectile 소환위치에 관여

public:
	DiceBase(int slot, int eye = 1);
	DiceBase(DiceBase& Dice);
	~DiceBase();

	BOOL operator==(const DiceBase& Dice2);
	BOOL IsReadyToDel() { return bReadyToDel; };
	void StopTr();
	void DrawObject(HDC hdc);
	vector<RECT> GetEyeLoc(int eye);
	void SetSlot(int slot);
	int GetSlot() const;

	float GetSpeed() const;

	shared_ptr<ProjectileBase> SpawnProj();
	
	void AddEye(int eye);
	bool IsOverlappedPoint(const POINT TargetPoint) const;
	void SetSelected(BOOL IsSelected);
	//void ReDraw(HWND hWnd);
	void MoveToMouse(POINT point);
	int GetEye() const;
	
};

