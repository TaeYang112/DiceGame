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
	POINT MousePos;								// 마우스 좌표

	HPEN oldPen;																			
	HBRUSH oldBrush;

	vector<ButtonObject> v_Button;
	vector<shared_ptr<DiceBase>> v_Dice;
	list<shared_ptr<MonsterBase>> l_Monster;	// 중간에서 삭제하기 위해 리스트 사용
	list<shared_ptr<ProjectileBase>> l_Projectile;

	ButtonObject Purchase;						// 주사위 구매버튼

	unique_ptr<DiceBase> DraggingDice;			// 주사위를 드래그할때 임시로 생성되는 객체
	DiceBase* DraggedDice;						// 드래그 되었던 객체의 주소를 임시로 저장함
	BOOL bDragging;								// 현재 드래그중인지 상태정보를 갖는 변수. TRUE 인동안 DraggedDice != nullptr 보장해야함

	int DiceCount;								// 현재 다이스 개수. 슬롯에 빈공간이 있는지 체크하기 위해 사용


	HANDLE Proj_SemaHnd;						// Projectile 리스트에 접근을 관리하는 세마포 핸들
	HANDLE Monster_SemaHnd;						// Monster 접근 관리 세마포 핸들
	HANDLE Money_SemaHnd;

	int Price;
	int Money;
	static GameHandler* Instance;				// GameHandler 싱글톤 객체를 static변수로 보관
private:
	GameHandler();								// 싱글톤 패턴을 위해 private
	~GameHandler();
public:

	static GameHandler* GetInstance();			// GameHandler 객체 얻기
	void DestroyInst();							// GameHandler 객체 제거

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawGame(HDC hdc);						// 게임의 전체적인 내용을 그림

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);				// MoveToEx와 LineTo 를 대체

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);		// SetDCPen과 SetDCBrush를 한번에 함
	void ClearDCColor(HDC hdc);											// DC의 색을 되돌림 ( 흰색 Brush, 검정 Pen )

	void OnMouseClicked(int x, int y);									// WM_LBUTTONDOWN에서 호출


	BOOL IsDragging() const;
	void AddMoney(int newMoney);
	void OnMouseMoved();												// WM_MOSUEMOVE에서 호출
	void OnMouseReleased(int x, int y);									// WM_LBUTTONUP에서 호출

	void DeleteMonster(MonsterBase *Monster);							// MonsterTr이 끝날때 자신을 참조하는 객체의 동작이 끝날때 까지 기다린후, List에서 자신 제거
	void DeleteProjectile(ProjectileBase* Projectile);
	//void DeleteDice(DiceBase* Dice);
	
	void AddProjectile(shared_ptr<ProjectileBase> Proj);				// 다이스가 생성한 Projectile을 리스트에 등록
	void SpawnMonster(MONSTER Type, int HP);
	shared_ptr<MonsterBase> GetFrontMonster() const;
};
