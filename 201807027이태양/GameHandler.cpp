
#include "GameHandler.h"
#include "resource.h"
#include "DiceBase.h"
#include <ctime>
#include <cstdlib>

GameHandler::GameHandler()
{
    MousePos = { 0,0 };
    oldPen = nullptr;
    oldBrush = nullptr;
    DraggingDice = nullptr;

    v_DiceArr.assign(15, nullptr);
    bDragging = FALSE;
    // 구매버튼
    Purchase.SetBounds(305, 450, 405, 550); 
    Purchase.SetClickAction([this](HWND hWnd) 
        {
            int r;
            while (1)
            {
                r = rand() % 15;
                if (v_DiceArr[r] == nullptr) break;
            }
            
            v_DiceArr[r] = make_shared<DiceBase>(r, 1);
            v_DiceArr[r]->ReDraw(hWnd);
        });
    Purchase.SetDrawAtion([this](HDC hdc)
        {
            SetDCColor(hdc, RGB(180, 180, 180), RGB(170, 170, 170));
            Ellipse(hdc, 305, 450, 405, 550);
        });
    v_ButtonArr.push_back(Purchase);
    

    srand((unsigned int)time(NULL));


}

GameHandler::~GameHandler()
{

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

void GameHandler::DrawFrame(HWND hWnd, HDC hdc)
{
    // 현재 HINSTANCE
    HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);    

    // 간편한 색 변경을 위해 DC_PEN 사용
    oldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));                   
    oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

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



    //주사위
    for (int i = 0; i < (int)v_DiceArr.size(); i++)
    {
        if (v_DiceArr[i] == nullptr) continue;
        v_DiceArr[i]->DrawDice(hWnd, hdc);
    }
    
    // 드래그중인 임시 주사위
    if (IsDragging() == TRUE)
    {
        DraggingDice->DrawDice(hWnd, hdc);
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

void GameHandler::OnMouseClicked(HWND hWnd,int x, int y)  // WM_LBUTTONDOWN 에서 호출
{
    
    for (int i = 0; i < (int)v_ButtonArr.size(); i++)   
    {
        if (v_ButtonArr[i].IsOverlappedPoint(x, y))     // 클릭한 위치가 버튼의 범위 내에 있을경우 참
        {
            v_ButtonArr[i].OnClickedObject(hWnd);       // 버튼에 등록한 함수를 실행
        }
    }
    for (int i = 0; i < (int)v_DiceArr.size(); i++)
    {
        if (v_DiceArr[i] == nullptr) continue;
        if (v_DiceArr[i]->IsOverlappedPoint(x, y))      // 클릭한 위치가 주사위의 범위 내에 있을경우 참
        {
            if (bDragging == FALSE)                    // 현재 드래그중이 아니라면
            {
                DraggedDice = v_DiceArr[i].get();             // 원본 객체 주소 저장, 원본객체는 가만히 있음

                DraggingDice = make_unique<DiceBase>(*DraggedDice);     // 스마트 포인터 이용하여 클릭한 다이스를 복사 생성 / 마우스에 드래깅되는 객체

                DraggedDice->SetSelected(TRUE);
                DraggedDice->ReDraw(hWnd);
                bDragging = TRUE;

                break;
            }
        }
    }
}

void GameHandler::OnMouseMoved(HWND hWnd)
{
    if (DraggingDice == nullptr) return;
    DraggingDice->MoveToMouse(hWnd, GetMousePos());

}

void GameHandler::OnMouseReleased(HWND hWnd, int x, int y)  // WM_LBUTTONUP 에서 호출
{
    if (IsDragging() == TRUE)       // 드래그중이였다면
    {


        // 다이스끼리의 겹침과 상관없이 실행되는 부분. 드래그를 취소함

        bDragging = FALSE;                          // 드래깅 끝냄
        DraggingDice.reset(nullptr);                // 마우스를 따라다니는 임시 객체를 delete하고 변수를 nullptr로 변경

        DraggedDice->SetSelected(FALSE);            // 색상 돌려놓음
        

        if (DraggedDice->GetEye() < 6)        // 눈이 6이상일 경우 겹쳐도 처리 할게 없음
        {

            for (int i = 0; i < (int)v_DiceArr.size(); i++)     // 모든 주사위 탐색
            {

                if (v_DiceArr[i] == nullptr) continue;
                if (v_DiceArr[i]->IsOverlappedPoint(x, y))      // 마우스를 떼었던 위치가 주사위와 겹친다면
                {
                    if (*v_DiceArr[i] == *DraggedDice)          // 타입과 주사위 눈이 서로 같을 경우
                    {
                        if (v_DiceArr[i].get() == DraggedDice) continue;     // 자기 자신은 예외
                        v_DiceArr[i]->AddEye(1);                // 눈을 증가시킴

                        delete DraggedDice;                     // 드래그중이던 주사위 제거
                        break;
                    }
                }
            }
        }
        

        DraggedDice = nullptr;                              

        InvalidateRect(hWnd, NULL, FALSE);
    }
}

BOOL GameHandler::IsDragging() const
{
    return bDragging;
}

