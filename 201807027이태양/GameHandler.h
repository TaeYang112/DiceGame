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
	static GameHandler* Instance;				// GameHandler 싱글톤 객체를 static변수로 보관

	int Price;
	int Money;
	int HP;
	int DIceUpgradeNum[6];						// 다이스별 강화정도

	int DiceCount;								// 현재 다이스 개수. 슬롯에 빈공간이 있는지 체크하기 위해 사용
	HFONT HPFont;								// HP를 표시하기 위한 폰트
	HFONT MoneyFont;							// Price를 표시하기 위한 폰트
	HFONT TopFont;								// 상단바를 표시하기 위한 폰트

	POINT MousePos;								// 마우스 좌표

	
	vector<shared_ptr<DiceBase>> v_Dice;
	list<shared_ptr<MonsterBase>> l_Monster;	// 중간에서 삭제하기 위해 리스트 사용
	list<shared_ptr<ProjectileBase>> l_Projectile;

	vector<shared_ptr<ButtonObject>> v_Button;				// 여러 버튼들을 관리하는 벡터 / Click을 호출해줌
	shared_ptr<ButtonObject> Purchase;						// 주사위 구매버튼
	shared_ptr<ButtonObject> UpgradeBtn[5];					// 주사위 강화버튼

	unique_ptr<DiceBase> DraggingDice;			// 주사위를 드래그할때 임시로 생성되는 객체
	DiceBase* DraggedDice;						// 드래그 되었던 객체의 주소를 임시로 저장함
	BOOL bDragging;								// 현재 드래그중인지 상태정보를 갖는 변수. TRUE 인동안 DraggedDice != nullptr 보장해야함



	HANDLE Proj_SemaHnd;						// Projectile 리스트에 접근을 관리하는 세마포 핸들
	HANDLE Monster_SemaHnd;						// Monster 접근 관리 세마포 핸들
	HANDLE Money_SemaHnd;
	HANDLE HP_SemaHnd;

	HANDLE PlayTRHnd;
	
	int GameState;								// 0 == 시작전, 1 == 게임중

	static HWND hWnd;
	
private:
	GameHandler();								// 싱글톤 패턴을 위해 private
	~GameHandler();
public:

	static GameHandler* GetInstance();			// GameHandler 객체 얻기
	void DestroyInst();							// GameHandler 객체 제거

	void SetHWND(HWND hWnd);

	void ButtonInit();

	void GameOver();

	void GameStart();

	int GetGameState() const;

	POINT GetMousePos() const;
	void SetMousePos(int x, int y);

	void DrawGame(HDC hdc);						// 게임의 전체적인 내용을 그림

	void DrawLine(HDC hdc, int x, int y, int x2, int y2);				// MoveToEx와 LineTo 를 대체

	void SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color);		// SetDCPen과 SetDCBrush를 한번에 함
	void ClearDCColor(HDC hdc);											// DC의 색을 되돌림 ( 흰색 Brush, 검정 Pen )

	void OnMouseClicked(int x, int y);									// WM_LBUTTONDOWN에서 호출


	BOOL IsDragging() const;
	void AddMoney(int newMoney);
	void AddHP(int newHP);
	void AddUpgradeNum(DICETYPE type, int num);
	int GetUpgradeNum(DICETYPE type);
	void OnMouseMoved();												// WM_MOSUEMOVE에서 호출
	void OnMouseReleased(int x, int y);									// WM_LBUTTONUP에서 호출

	void DeleteMonster(MonsterBase *Monster);							// MonsterTr이 끝날때 자신을 참조하는 객체의 동작이 끝날때 까지 기다린후, List에서 자신 제거
	void DeleteProjectile(ProjectileBase* Projectile);
	//void DeleteDice(DiceBase* Dice);
	
	void AddProjectile(shared_ptr<ProjectileBase> Proj);				// 다이스가 생성한 Projectile을 리스트에 등록
	void SpawnMonster(MONSTER Type, int HP);
	void SpawnDice(int slot);
	shared_ptr<MonsterBase> GetMonsterRef(ATKTYPE Type) const;
};
