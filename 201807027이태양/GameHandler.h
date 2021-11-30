#pragma once
#include <vector>
#include <list>
#include "framework.h"
#include "ButtonObject.h" 
#include "DiceBase.h"
#include <memory>

using namespace std;

class DiceBase;
class MonsterBase;
class ProjectileBase;
class GameHandler
{

private:
	POINT MousePos;								// ���콺 ��ǥ

	HPEN oldPen;																			
	HBRUSH oldBrush;

	vector<ButtonObject> v_Button;
	vector<shared_ptr<DiceBase>> v_Dice;
	list<shared_ptr<MonsterBase>> l_Monster;	// �߰����� �����ϱ� ���� ����Ʈ ���
	list<shared_ptr<ProjectileBase>> l_Projectile;

	ButtonObject Purchase;						// �ֻ��� ���Ź�ư

	unique_ptr<DiceBase> DraggingDice;			// �ֻ����� �巡���Ҷ� �ӽ÷� �����Ǵ� ��ü
	DiceBase* DraggedDice;						// �巡�� �Ǿ��� ��ü�� �ּҸ� �ӽ÷� ������
	BOOL bDragging;								// ���� �巡�������� ���������� ���� ����. TRUE �ε��� DraggedDice != nullptr �����ؾ���

	int DiceCount;								// ���� ���̽� ����. ���Կ� ������� �ִ��� üũ�ϱ� ���� ���


	HANDLE Proj_SemaHnd;						// Projectile ����Ʈ�� ������ �����ϴ� ������ �ڵ�
	HANDLE Monster_SemaHnd;						// Monster ���� ���� ������ �ڵ�
	HANDLE Money_SemaHnd;

	int Price;
	int Money;
	static GameHandler* Instance;				// GameHandler �̱��� ��ü�� static������ ����
private:
	GameHandler();								// �̱��� ������ ���� private
	~GameHandler();
public:

	static GameHandler* GetInstance();			// GameHandler ��ü ���
	void DestroyInst();							// GameHandler ��ü ����

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawGame(HDC hdc);						// ������ ��ü���� ������ �׸�

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);				// MoveToEx�� LineTo �� ��ü

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);		// SetDCPen�� SetDCBrush�� �ѹ��� ��
	void ClearDCColor(HDC hdc);											// DC�� ���� �ǵ��� ( ��� Brush, ���� Pen )

	void OnMouseClicked(int x, int y);									// WM_LBUTTONDOWN���� ȣ��


	BOOL IsDragging() const;
	void AddMoney(int newMoney);
	void OnMouseMoved();												// WM_MOSUEMOVE���� ȣ��
	void OnMouseReleased(int x, int y);									// WM_LBUTTONUP���� ȣ��

	void DeleteMonster(MonsterBase *Monster);							// MonsterTr�� ������ �ڽ��� �����ϴ� ��ü�� ������ ������ ���� ��ٸ���, List���� �ڽ� ����
	void DeleteProjectile(ProjectileBase* Projectile);
	//void DeleteDice(DiceBase* Dice);
	
	void AddProjectile(shared_ptr<ProjectileBase> Proj);				// ���̽��� ������ Projectile�� ����Ʈ�� ���
	void SpawnMonster(MONSTER Type, int HP);
	shared_ptr<MonsterBase> GetFrontMonster() const;
};
