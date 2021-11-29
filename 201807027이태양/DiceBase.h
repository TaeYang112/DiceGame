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
	int Slot;			// ����
	int Power;			// ������
	float AttackSpeed;	// ���ݼӵ�
	int DiceEye;		// �ֻ��� �� ( 1 ~ 6 )
	COLORREF Color;		// �׵θ� ��
	BOOL IsSelected;
	int DiceType;		// ���̽� ����
	BOOL bReadyToDel;
	int AttackCount;	// ����Ƚ��.  Projectile ��ȯ��ġ�� ����

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

