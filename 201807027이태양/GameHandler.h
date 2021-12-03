#pragma once
#include <vector>
#include <list>
#include "framework.h"
#include "MonsterBase.h"
#include "DiceBase.h"
#include <memory>

using namespace std;


class DiceBase;
class MonsterBase;
class ProjectileBase;
class ButtonObject;
class GameHandler
{

private:
	static GameHandler* Instance;				// GameHandler �̱��� ��ü�� static������ ����

	int Price;
	int Money;
	int HP;
	int DIceUpgradeNum[6];						// ���̽��� ��ȭ����

	int DiceCount;								// ���� ���̽� ����. ���Կ� ������� �ִ��� üũ�ϱ� ���� ���
	HFONT HPFont;								// HP�� ǥ���ϱ� ���� ��Ʈ
	HFONT MoneyFont;							// Price�� ǥ���ϱ� ���� ��Ʈ
	HFONT TopFont;								// ��ܹٸ� ǥ���ϱ� ���� ��Ʈ

	POINT MousePos;								// ���콺 ��ǥ

	
	vector<shared_ptr<DiceBase>> v_Dice;
	list<shared_ptr<MonsterBase>> l_Monster;	// �߰����� �����ϱ� ���� ����Ʈ ���
	list<shared_ptr<ProjectileBase>> l_Projectile;

	vector<shared_ptr<ButtonObject>> v_Button;				// ���� ��ư���� �����ϴ� ���� / Click�� ȣ������
	shared_ptr<ButtonObject> Purchase;						// �ֻ��� ���Ź�ư
	shared_ptr<ButtonObject> UpgradeBtn[5];					// �ֻ��� ��ȭ��ư

	unique_ptr<DiceBase> DraggingDice;			// �ֻ����� �巡���Ҷ� �ӽ÷� �����Ǵ� ��ü
	DiceBase* DraggedDice;						// �巡�� �Ǿ��� ��ü�� �ּҸ� �ӽ÷� ������
	BOOL bDragging;								// ���� �巡�������� ���������� ���� ����. TRUE �ε��� DraggedDice != nullptr �����ؾ���



	HANDLE Proj_SemaHnd;						// Projectile ����Ʈ�� ������ �����ϴ� ������ �ڵ�
	HANDLE Monster_SemaHnd;						// Monster ���� ���� ������ �ڵ�
	HANDLE Money_SemaHnd;
	HANDLE HP_SemaHnd;

	HANDLE PlayTRHnd;
	
	int GameState;								// 0 == ������, 1 == ������

	static HWND hWnd;
	
private:
	GameHandler();								// �̱��� ������ ���� private
	~GameHandler();
public:

	static GameHandler* GetInstance();			// GameHandler ��ü ���
	void DestroyInst();							// GameHandler ��ü ����

	void SetHWND(HWND hWnd);

	void ButtonInit();

	void GameOver();

	void GameStart();

	int GetGameState() const;

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawGame(HDC hdc);						// ������ ��ü���� ������ �׸�

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);				// MoveToEx�� LineTo �� ��ü

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);		// SetDCPen�� SetDCBrush�� �ѹ��� ��
	void ClearDCColor(HDC hdc);											// DC�� ���� �ǵ��� ( ��� Brush, ���� Pen )

	void OnMouseClicked(int x, int y);									// WM_LBUTTONDOWN���� ȣ��


	BOOL IsDragging() const;
	void AddMoney(int newMoney);
	void AddHP(int newHP);
	void AddUpgradeNum(DICETYPE type, int num);
	int GetUpgradeNum(DICETYPE type);
	void OnMouseMoved();												// WM_MOSUEMOVE���� ȣ��
	void OnMouseReleased(int x, int y);									// WM_LBUTTONUP���� ȣ��

	void DeleteMonster(MonsterBase *Monster);							// MonsterTr�� ������ �ڽ��� �����ϴ� ��ü�� ������ ������ ���� ��ٸ���, List���� �ڽ� ����
	void DeleteProjectile(ProjectileBase* Projectile);
	//void DeleteDice(DiceBase* Dice);
	
	void AddProjectile(shared_ptr<ProjectileBase> Proj);				// ���̽��� ������ Projectile�� ����Ʈ�� ���
	void SpawnMonster(MONSTER Type, int HP);
	void SpawnDice(int slot);
	shared_ptr<MonsterBase> GetMonsterRef(ATKTYPE Type) const;
};
