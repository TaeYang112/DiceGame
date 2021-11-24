

#include "GameHandler.h"
#include "resource.h"
#include "DiceBase.h"
#include "MonsterBase.h"
#include "ButtonObject.h"
#include <ctime>
#include <cstdlib>

DWORD WINAPI MoveMonster(LPVOID Param); 
DWORD WINAPI MonsterTr(LPVOID Param);
DWORD WINAPI IDRTimer(LPVOID Param);

HWND g_hWnd;
GameHandler::GameHandler(HWND hWnd) : Purchase({ 305,450 }, 100, 100)
{
    MousePos = { 0,0 };
    oldPen = nullptr;
    oldBrush = nullptr;
    DraggingDice = nullptr;
    DiceCount = 0;
    g_hWnd = hWnd;

    v_DiceArr.assign(15, nullptr);
    bDragging = FALSE;

    srand((unsigned int)time(NULL));

    // 구매버튼
    Purchase.SetClickAction([this](HWND hWnd) 
        {
            if (DiceCount >= 15) return; // 주사위 자리가 없다면 리턴

            int r;
            while (1)
            {
                r = rand() % 15;
                if (v_DiceArr[r] == nullptr) break;
            }
            
            v_DiceArr[r] = make_shared<DiceBase>(r, 1);
            v_DiceArr[r]->ReDraw(hWnd);
            DiceCount++;
                
            l_MonsterArr.push_back(make_shared<MonsterBase>(90));
            CreateThread(NULL, 0, MonsterTr, l_MonsterArr.back().get(), 0, NULL);
        });
    Purchase.SetDrawAtion([this](HDC hdc)
        {
            SetDCColor(hdc, RGB(180, 180, 180), RGB(170, 170, 170));
            Ellipse(hdc, 305, 450, 405, 550);
        });
    v_ButtonArr.push_back(Purchase);


    IDRHandle =  CreateThread(NULL, 0, IDRTimer, NULL, 0, NULL);

    //디버그
    

    


}

GameHandler::~GameHandler()
{
    SuspendThread(IDRHandle);       // InvalidRect 쓰레드 종료
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

void GameHandler::DrawFrame(HDC hdc)
{
    // 현재 HINSTANCE
    HINSTANCE hInst = (HINSTANCE)GetWindowLong(g_hWnd, GWL_HINSTANCE);    

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
    auto it = l_MonsterArr.rbegin();
    while (it != l_MonsterArr.rend())                   // 먼저 소환한 몬스터가 겹친 몬스터중 맨앞에 위치
    {
        if ((*it)->IsDead())                            // 죽었으면
        {
            l_MonsterArr.erase(std::next(it).base());   // 리스트에서 제거
            continue;
        }
        (*it)->DrawObject(hdc);
        it++;
    }


    //주사위
    for (int i = 0; i < 15; i++)
    {
        if (v_DiceArr[i] == nullptr) continue;
        v_DiceArr[i]->DrawObject(hdc);
    }
    
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

    if (P_Color == NULL) SetDCPenColor(hdc, B_Color);
    else SetDCPenColor(hdc, P_Color);
}

void GameHandler::ClearDCColor(HDC hdc)
{
    SetDCBrushColor(hdc, RGB(255, 255, 255));
    SetDCPenColor(hdc, RGB(0, 0, 0));
}

void GameHandler::OnMouseClicked(int x, int y)  // WM_LBUTTONDOWN 에서 호출
{
    
    for (int i = 0; i < (int)v_ButtonArr.size(); i++)   
    {
        if (v_ButtonArr[i].IsOverlappedPoint(x, y))     // 클릭한 위치가 버튼의 범위 내에 있을경우 참
        {
            v_ButtonArr[i].OnClickedObject(g_hWnd);       // 버튼에 등록한 함수를 실행
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (v_DiceArr[i] == nullptr) continue;
        if (v_DiceArr[i]->IsOverlappedPoint({ x,y }))      // 클릭한 위치가 주사위의 범위 내에 있을경우 참
        {
            if (bDragging == FALSE)                    // 현재 드래그중이 아니라면
            {
                DraggedDice = v_DiceArr[i].get();             // 원본 객체 주소 저장, 원본객체는 가만히 있음

                DraggingDice = make_unique<DiceBase>(*DraggedDice);     // 스마트 포인터 이용하여 클릭한 다이스를 복사 생성 / 마우스에 드래깅되는 객체
                DraggingDice->MoveToMouse(GetMousePos());

                DraggedDice->SetSelected(TRUE);
                DraggedDice->ReDraw(g_hWnd);                            
                bDragging = TRUE;

                break;
            }
        }
    }
}

void GameHandler::OnMouseMoved()
{
    if (DraggingDice == nullptr) return;
    DraggingDice->MoveToMouse(GetMousePos());
    //InvalidateRect(g_hWnd, NULL, FALSE);
}

void GameHandler::OnMouseReleased(int x, int y)  // WM_LBUTTONUP 에서 호출
{
    if (IsDragging() == TRUE)       // 드래그중이였다면
    {


        // 다이스끼리의 겹침과 상관없이 실행되는 부분. 드래그를 취소함

        bDragging = FALSE;                          // 드래깅 끝냄
        DraggingDice.reset(nullptr);                // 마우스를 따라다니는 임시 객체를 delete하고 변수를 nullptr로 변경

        DraggedDice->SetSelected(FALSE);            // 색상 돌려놓음
        

        if (DraggedDice->GetEye() < 6)        // 눈이 6이하의 주사위 일때
        {

            for (int i = 0; i < 15; i++)     // 모든 주사위 탐색
            {

                if (v_DiceArr[i] == nullptr) continue;
                if (v_DiceArr[i]->IsOverlappedPoint({ x,y }))      // 마우스를 떼었던 위치가 주사위와 겹친다면
                {
                    if (*v_DiceArr[i] == *DraggedDice)          // 타입과 주사위 눈이 서로 같을 경우
                    {
                        if (v_DiceArr[i].get() == DraggedDice) continue;     // 자기 자신은 예외
                        v_DiceArr[i]->AddEye(1);                // 눈을 증가시킴

                        int temp = DraggedDice->GetSlot();
                        v_DiceArr[temp].reset();
                        DraggedDice = nullptr;                     // 드래그중이던 주사위 제거
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

// 세마포 사용해보려고 미사용, 스레드 1개로 모든 몬스터 움직임
DWORD WINAPI MoveMonster(LPVOID Param)
{
    list<shared_ptr<MonsterBase>> *l_MonsterArr = (list<shared_ptr<MonsterBase>>*)Param;
   
    while (1)
    {
       
        for (auto it = l_MonsterArr->begin(); it != l_MonsterArr->end(); it++)
        {
            it->get()->MoveNextPoint();
        }
        Sleep(16);
    }
    return 0;
}
// 사용중, 몬스터마다 스레드 부여
DWORD WINAPI MonsterTr(LPVOID Param)
{
   MonsterBase* Monster = (MonsterBase*)Param;
   while (1)
    {
        BOOL bMoveEnd = !Monster->MoveNextPoint();   // 몬스터 이동. 만약 끝 지점에 도착하면 FALSE 반환
        
        if (bMoveEnd) break;

       Sleep(17);
    }
    Monster->SetDead();
    ExitThread(0);
    return 0;
}


DWORD WINAPI IDRTimer(LPVOID Param)
{
    while (1) // 초당 100번 반복
    {
        InvalidateRect(g_hWnd, NULL, FALSE);
        Sleep(10);
    }
    return 0;
}