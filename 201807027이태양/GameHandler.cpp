#include "GameHandler.h"
#include "resource.h"

#include "MonsterBase.h"
#include "ButtonObject.h"
#include "ProjectileBase.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <cstdlib>

DWORD WINAPI MonsterTr(LPVOID Param);
DWORD WINAPI DiceTr(LPVOID Param);
GameHandler* GameHandler::Instance = nullptr;
//HWND g_hWnd;



GameHandler::GameHandler() : Purchase({ 305,450 }, 100, 100)
{
    MousePos = { 0,0 };
    oldPen = nullptr;
    oldBrush = nullptr;
    DraggingDice = nullptr;
    DiceCount = 0;
    //g_hWnd = hWnd;

    v_Dice.assign(15, nullptr);
    bDragging = FALSE;

    srand((unsigned int)time(NULL));

    // 구매버튼
    Purchase.SetClickAction([this]() 
        {
            if (DiceCount >= 15) return; // 주사위 자리가 없다면 리턴

            int r;
            while (1)
            {
                r = rand() % 15;
                if (v_Dice[r] == nullptr) break;
            }
            
            v_Dice[r] = make_shared<DiceBase>(r, 1);
            HANDLE hnd = CreateThread(NULL, 0, DiceTr, &v_Dice[r], 0, NULL);
            v_Dice[r]->SetTRHandle(hnd);
            //v_Dice[r]->ReDraw(hWnd);
            DiceCount++;
                
            l_Monster.push_back(make_shared<MonsterBase>(90));
            CreateThread(NULL, 0, MonsterTr, &l_Monster.back(), 0, NULL);
        });
    Purchase.SetDrawAtion([this](HDC hdc)
        {
            SetDCColor(hdc, RGB(180, 180, 180), RGB(170, 170, 170));
            Ellipse(hdc, 305, 450, 405, 550);
        });
    v_Button.push_back(Purchase);


    //IDRHandle =  CreateThread(NULL, 0, IDRTimer, NULL, 0, NULL);

    Proj_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
    Monster_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
    //디버그

}

GameHandler::~GameHandler()
{
    if( Proj_SemaHnd != NULL) CloseHandle(Proj_SemaHnd);
    
}



GameHandler* GameHandler::GetInstance()
{
    if (!Instance)
    {
        Instance = new GameHandler();
    }
    return Instance;
}
void GameHandler::DestroyInst()
{
    if (Instance)
    {
        delete Instance;
    }
}
POINT GameHandler::GetMousePos() const
{
	return MousePos;
}

void GameHandler::SetMousePos(int x, int y)
{
	MousePos.x = x;
	MousePos.y = y;
}

void GameHandler::DrawGame(HDC hdc)
{

    // 간편한 색 변경을 위해 DC_PEN 사용
    oldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));                   
    oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

    SetBkMode(hdc, TRANSPARENT);    // 출력되는 모든 글자의 배경이 투명해짐

    // 게임 테두리 그림자
    SetDCColor(hdc, RGB(200,200,200), NULL);
    RoundRect(hdc, 30, 20, 700, 700, 30, 30);              
    ClearDCColor(hdc);  

    // 게임 테두리
    RoundRect(hdc, 20, 0, 690, 690, 30, 30);      

    // 게임 상단바 (시간 표시 영역)
    SetDCColor(hdc, RGB(100, 100, 100),PS_NULL);;           
    RoundRect(hdc, 20, 0, 690, 70, 30,30);               
    // 게임 상단바 RoundRect의 밑부분을 흰 사각형으로 가림
    SetDCColor(hdc, RGB(255, 255, 255), NULL);
    Rectangle(hdc, 21, 56, 689, 100);     
    
    // 주사위 컨테이너 그림자
    SetDCColor(hdc, RGB(240, 240, 240), NULL);
    RoundRect(hdc, 130, 170, 580, 425, 30, 30);

    

    // 주사위 컨테이너
    HPEN newPen = CreatePen(PS_SOLID, 3, RGB(200, 200, 200));    
    SelectObject(hdc, newPen);
    SelectObject(hdc, oldBrush);

    RoundRect(hdc, 135, 175, 575, 420, 30, 30);

    DeleteObject(newPen);
    

    // 몬스터 진행방향
    newPen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
    SelectObject(hdc, newPen);

    DrawLine(hdc, 55, 120, 55, 420);
    DrawLine(hdc, 55, 120, 655, 120);
    DrawLine(hdc, 655, 120, 655, 420);

    DeleteObject(newPen);

    // 다시 DC_PEN 사용
    SelectObject(hdc, GetStockObject(DC_PEN));
    SelectObject(hdc, GetStockObject(DC_BRUSH));





    
    // 주사위 슬롯
    SetDCColor(hdc, RGB(220, 220, 220), NULL);
    int y = 188;
    for (int i = 0; i < 3; i++)
    {
        int x = 155;
        for (int j = 0; j < 5; j++)
        {
            RoundRect(hdc, x, y, x + 70, y + 70,20,20);
            x += 83;
        }
        y += 72;
    }

    // 주사위 구매버튼 바깥 ( 버튼 객체 )
    Purchase.DrawObject(hdc);

    // 주사위 구매버튼 안쪽
    SetDCColor(hdc, RGB(220, 220, 220), RGB(210, 210, 210));
    Ellipse(hdc, 315, 460, 395, 540);

    // 구매버튼의 주사위
    SetDCColor(hdc, RGB(255, 255, 255), RGB(1, 1, 1));
    Rectangle(hdc, 340, 465, 370, 495);
    // 구매버튼 주사위 눈
    SetDCColor(hdc, RGB(0, 0, 0), NULL);
    Ellipse(hdc, 345, 470, 350, 475);
    Ellipse(hdc, 360, 470, 365, 475);
    Ellipse(hdc, 345, 485, 350, 490);
    Ellipse(hdc, 360, 485, 365, 490);


    // 주사위 강화 컨테이너
    SetDCColor(hdc, RGB(220, 220, 220), NULL);
    RoundRect(hdc, 135, 575, 575, 680, 20, 20);

    
    // 몬스터 
    //WaitForSingleObject(Monster_SemaHnd, INFINITE);
    auto it = l_Monster.rbegin();
    while (it != l_Monster.rend())                   // 먼저 소환한 몬스터가 겹친 몬스터중 맨앞에 위치
    {
        if ((*it)->GetState() == STATE::ALIVE)         // 살아있지 않으면
        {
            (*it)->DrawObject(hdc);
        }
        it++;
    }
   // ReleaseSemaphore(Monster_SemaHnd, 1, NULL);

    

    // 주사위
    for (int i = 0; i < 15; i++)
    {
        if (v_Dice[i] == nullptr) continue;
        v_Dice[i]->DrawObject(hdc);
    }

    // 투사체
    WaitForSingleObject(Proj_SemaHnd, INFINITE);
    for (auto it = l_Projectile.begin(); it != l_Projectile.end(); it++)
    {
        (*it)->DrawObject(hdc);
    }
    ReleaseSemaphore(Proj_SemaHnd, 1, NULL);

    
    // 드래그중인 임시 주사위
    if (IsDragging() == TRUE)
    {
        DraggingDice->DrawObject(hdc);
    }


    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);

}

void GameHandler::DrawLine(HDC hdc, int x, int y, int x2, int y2)
{
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x2, y2);
}

void GameHandler::SetDCColor(HDC hdc, COLORREF B_Color, COLORREF P_Color)
{

    SetDCBrushColor(hdc, B_Color);

    if (P_Color == NULL) SetDCPenColor(hdc, B_Color);    else SetDCPenColor(hdc, P_Color);
}

void GameHandler::ClearDCColor(HDC hdc)
{
    SetDCBrushColor(hdc, RGB(255, 255, 255));
    SetDCPenColor(hdc, RGB(0, 0, 0));
}

void GameHandler::OnMouseClicked(int x, int y)                  // WM_LBUTTONDOWN 에서 호출
{
    
    for (int i = 0; i < (int)v_Button.size(); i++)   
    {
        if (v_Button[i].IsOverlappedPoint(x, y))                // 클릭한 위치가 버튼의 범위 내에 있을경우 참
        {
            v_Button[i].OnClickedObject();                      // 버튼에 등록한 함수를 실행
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (v_Dice[i] == nullptr) continue;
        if (v_Dice[i]->IsOverlappedPoint({ x,y }))              // 클릭한 위치가 주사위의 범위 내에 있을경우 참
        {
            if (bDragging == FALSE)                             // 현재 드래그중이 아니라면
            {
                DraggedDice = v_Dice[i].get();                  // 원본 객체 주소 저장, 원본객체는 가만히 있음

                DraggingDice = make_unique<DiceBase>(*DraggedDice);     // 스마트 포인터 이용하여 클릭한 다이스를 복사 생성 / 마우스에 드래깅되는 객체
                DraggingDice->MoveToMouse(GetMousePos());

                DraggedDice->SetSelected(TRUE);
                //DraggedDice->ReDraw();                            
                bDragging = TRUE;

                break;
            }
        }
    }
}

// WM_MOUSEMOVE 에서 호출
void GameHandler::OnMouseMoved()
{
    if (DraggingDice == nullptr) return;
    DraggingDice->MoveToMouse(GetMousePos());
    //InvalidateRect(g_hWnd, NULL, FALSE);
}

// WM_LBUTTONUP 에서 호출
void GameHandler::OnMouseReleased(int x, int y)             
{
    if (IsDragging() == TRUE)                               // 드래그중이였다면
    {


        // 다이스끼리의 겹침과 상관없이 실행되는 부분. 드래그를 취소함

        bDragging = FALSE;                                                  // 드래깅 끝냄
        DraggingDice.reset(nullptr);                                        // 마우스를 따라다니는 임시 객체를 delete하고 변수를 nullptr로 변경

        DraggedDice->SetSelected(FALSE);                                    // 색상 돌려놓음
        

        if (DraggedDice->GetEye() < 6)                                      // 눈이 6이하의 주사위 일때
        {

            for (int i = 0; i < 15; i++)                                    // 모든 주사위 탐색
            {

                if (v_Dice[i] == nullptr) continue;
                if (v_Dice[i]->IsOverlappedPoint({ x,y }))                  // 마우스를 떼었던 위치가 주사위와 겹친다면
                {
                    if (*v_Dice[i] == *DraggedDice)                         // 타입과 주사위 눈이 서로 같을 경우
                    {
                        if (v_Dice[i].get() == DraggedDice) continue;       // 자기 자신은 예외
                        v_Dice[i]->AddEye(1);                               // 눈을 증가시킴

                        int temp = DraggedDice->GetSlot();
                        v_Dice[temp]->StopTr();
                        v_Dice[temp].reset();
                        DraggedDice = nullptr;                              // 드래그중이던 주사위 제거
                        DiceCount--;
                        break;
                    }
                }
            }
        }
        

        DraggedDice = nullptr;                              

        //InvalidateRect(g_hWnd, NULL, FALSE);
    }
}

BOOL GameHandler::IsDragging() const
{
    return bDragging;
}


// MonsterTr 종료전 Monster객체를 소멸시키고 리스트에서 제거하기 위한 함수
void GameHandler::DeleteMonster(MonsterBase *Monster)            
{
    WaitForSingleObject(Monster_SemaHnd, INFINITE);
    for (auto it = l_Monster.begin(); it != l_Monster.end(); it++)
    {
        if (it->get() == Monster)                               
        {
            while (it->use_count() > 2)                         // l_Monster와 MonsterTr 이외에도 객체를 사용하고있다면 대기
            {     
                Sleep(10);                                     // 0.01초에 한번씩 체크
            }
            
            it = l_Monster.erase(it);
            
            break;
        }
    }
    ReleaseSemaphore(Monster_SemaHnd, 1, NULL);
    
}

//ProjectileTr 종료전 Projectile객체를 소멸시키고 리스트에서 제거하기 위한 함수
void GameHandler::DeleteProjectile(ProjectileBase* Projectile)             
{
    WaitForSingleObject(Proj_SemaHnd, INFINITE);
    for (auto it = l_Projectile.begin(); it != l_Projectile.end(); it++)
    {
        if (it->get() == Projectile)                           
        {
            it = l_Projectile.erase(it);
            break;
        }
    }
    ReleaseSemaphore(Proj_SemaHnd, 1, NULL);

}

void GameHandler::AddProjectile(shared_ptr<ProjectileBase> Proj)
{
    WaitForSingleObject(Proj_SemaHnd, INFINITE);
    l_Projectile.push_back(Proj);
    ReleaseSemaphore(Proj_SemaHnd, 1, NULL);   
}

shared_ptr<MonsterBase> GameHandler::GetFrontMonster() const
{
    WaitForSingleObject(Monster_SemaHnd, INFINITE);
    shared_ptr<MonsterBase> s = NULL;
   /* for (auto it = l_Monster.begin(); it != l_Monster.end(); it++)
    {
        if ((*it)->GetState() == STATE::ALIVE)
        {
            s = *it;
        }
    }*/
    if (!l_Monster.empty()) s = l_Monster.front();
    ReleaseSemaphore(Monster_SemaHnd, 1, NULL);
    return s;
}



// 몬스터마다 스레드 부여
DWORD WINAPI MonsterTr(LPVOID Param)
{
   shared_ptr<MonsterBase> Monster = *(shared_ptr<MonsterBase>*)Param;

   while (Monster->GetState() == STATE::ALIVE)
    {
        BOOL bMoveEnd = Monster->MoveNextPoint();   // 몬스터 이동. 만약 끝 지점에 도착하면 TRUE 반환
        
        if (bMoveEnd)
        {
            Monster->SetState(STATE::ARRIVAL);
            break;
        }

       Sleep(17);
    }   
    GameHandler::GetInstance()->DeleteMonster(Monster.get());
    return 0;
}



// 투사체 움직임
DWORD WINAPI ProjectileTr(LPVOID Param)
{
    shared_ptr<ProjectileBase> Projectile = ((pair<shared_ptr<ProjectileBase>, shared_ptr<MonsterBase>>*)Param)->first;
    shared_ptr<MonsterBase> Target = ((pair<shared_ptr<ProjectileBase>, shared_ptr<MonsterBase>>*)Param)->second;

    while (Target->GetState() == STATE::ALIVE) 
    {
        BOOL result = Projectile->MoveToTarget(Target.get()); // 이동 후  타겟과 겹치면 TRUE 반환
        if (result)
        {
            Target->TakeDamage(Projectile->GetPower());
            break;
        }
        else
        Sleep(17);
    }
    GameHandler::GetInstance()->DeleteProjectile(Projectile.get());
    return 0;
}

DWORD WINAPI DiceTr(LPVOID Param)
{
    shared_ptr<DiceBase> Dice = *(shared_ptr<DiceBase>*)Param;
    float AttackSpeed = Dice->GetSpeed();
    
    while (TRUE)
    {
        shared_ptr<MonsterBase> Target;
        Target = GameHandler::GetInstance()->GetFrontMonster();
        if (Target != NULL)
        {
            shared_ptr<ProjectileBase> Proj = Dice->SpawnProj();
            GameHandler::GetInstance()->AddProjectile(Proj);                    // 생성한 Projectile을 리스트에 등록. 동기화 되어있음

            pair<shared_ptr<ProjectileBase>, shared_ptr<MonsterBase>> rParam;
            rParam = make_pair(Proj, Target);

            CreateThread(NULL, 0, ProjectileTr, &rParam, 0, NULL);
        }
        Sleep(DWORD(AttackSpeed * 1000));
    }

    return 0;
}