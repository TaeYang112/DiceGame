#pragma once
#include "framework.h"
#include "ObjectBase.h"
#include <memory>
#include <vector>

#define DICE_BOLD 4
#define EYE_BOLD 10
enum class DICETYPE
{
	PURPLE=0,
	GRAY=1,
	ICE=2,
	SNIPER=3,
	BLACK = 4
};

enum class ATKTYPE
{
	FRONT,
	BACK,
	RANDOM
};

class ProjectileBase;
class DiceBase : ObjectBase
{

public:
	int Slot;			// ����
	int DiceEye;		// �ֻ��� �� ( 1 ~ 6 )
	BOOL IsSelected;
	BOOL bReadyToDel;
	int AttackCount;	// ����Ƚ��.  Projectile ��ȯ��ġ�� ����
protected:
	
	int Power;			// ������
	float AttackSpeed;	// ���� �ӵ�
	float ShotSpeed;	// ����ü �ӵ�
	ATKTYPE AttackType;
	DICETYPE DiceType;		// ���̽� ����
	COLORREF Color;		// �׵θ� ��
	DEBUFF Effect;
	float EffDuration;
	

public:
	DiceBase(int slot, int eye = 1);
	DiceBase(DiceBase& Dice);
	~DiceBase();

	BOOL operator==(const DiceBase& Dice2);
	BOOL IsReadyToDel() { return bReadyToDel; };
	void StopTr();
	virtual void DrawObject(HDC hdc);
	vector<RECT> GetEyeLoc(int eye);
	void SetSlot(int slot);
	int GetSlot() const;

	float GetSpeed() const;

	shared_ptr<ProjectileBase> SpawnProj(int Lv); 

	ATKTYPE GetAttackType() const;

	Debuff GetDebuff();


	DICETYPE GetType() const;
	
	void AddEye(int eye);
	virtual void EyeChanged();

	bool IsOverlappedPoint(const POINT TargetPoint) const;
	void SetSelected(BOOL IsSelected);
	//void ReDraw(HWND hWnd);
	void MoveToMouse(POINT point);
	int GetEye() const;
	
};

