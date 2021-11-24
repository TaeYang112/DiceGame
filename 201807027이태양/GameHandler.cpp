#include "GameHandler.h"
#include "resource.h"
#include "DiceBase.h"
#include "MonsterBase.h"
#include "ButtonObject.h"
#include "ProjectileBase.h"
#include <utility>
#include <ctime>
#include <cstdlib>

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

    v_Dice.assign(15, nullptr);
    bDragging = FALSE;

    srand((unsigned int)time(NULL));

    // ���Ź�ư
    Purchase.SetClickAction([this](HWND hWnd) 
        {
            if (DiceCount >= 15) return; // �ֻ��� �ڸ��� ���ٸ� ����

            int r;
            while (1)
            {
                r = rand() % 15;
                if (v_Dice[r] == nullptr) break;
            }
            
            v_Dice[r] = make_shared<DiceBase>(r, 1);
            v_Dice[r]->ReDraw(hWnd);
            DiceCount++;
                
            l_Monster.push_back(make_shared<MonsterBase>(90));
            CreateThread(NULL, 0, MonsterTr, l_Monster.back().get(), 0, NULL);
        });
    Purchase.SetDrawAtion([this](HDC hdc)
        {
            SetDCColor(hdc, RGB(180, 180, 180), RGB(170, 170, 170));
            Ellipse(hdc, 305, 450, 405, 550);
        });
    v_Button.push_back(Purchase);


    IDRHandle =  CreateThread(NULL, 0, IDRTimer, NULL, 0, NULL);

    //�����
    

    


}


GameHandler::~GameHandler()
{
    SuspendThread(IDRHandle);       // InvalidRect ������ ����
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

    // ������ �� ������ ���� DC_PEN ���
    oldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));                   
    oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

    SetBkMode(hdc, TRANSPARENT);    // ��µǴ� ��� ������ ����� ��������

    // ���� �׵θ� �׸���
    SetDCColor(hdc, RGB(200,200,200), NULL);
    RoundRect(hdc, 30, 20, 700, 700, 30, 30);              
    ClearDCColor(hdc);  

    // ���� �׵θ�
    RoundRect(hdc, 20, 0, 690, 690, 30, 30);      

    // ���� ��ܹ� (�ð� ǥ�� ����)
    SetDCColor(hdc, RGB(100, 100, 100),PS_NULL);;           
    RoundRect(hdc, 20, 0, 690, 70, 30,30);               
    // ���� ��ܹ� RoundRect�� �غκ��� �� �簢������ ����
    SetDCColor(hdc, RGB(255, 255, 255), NULL);
    Rectangle(hdc, 21, 56, 689, 100);     
    
    // �ֻ��� �����̳� �׸���
    SetDCColor(hdc, RGB(240, 240, 240), NULL);
    RoundRect(hdc, 130, 170, 580, 425, 30, 30);

    

    // �ֻ��� �����̳�
    HPEN newPen = CreatePen(PS_SOLID, 3, RGB(200, 200, 200));    
    SelectObject(hdc, newPen);
    SelectObject(hdc, oldBrush);

    RoundRect(hdc, 135, 175, 575, 420, 30, 30);

    DeleteObject(newPen);
    

    // ���� �������
    newPen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
    SelectObject(hdc, newPen);

    DrawLine(hdc, 55, 120, 55, 420);
    DrawLine(hdc, 55, 120, 655, 120);
    DrawLine(hdc, 655, 120, 655, 420);

    DeleteObject(newPen);

    // �ٽ� DC_PEN ���
    SelectObject(hdc, GetStockObject(DC_PEN));
    SelectObject(hdc, GetStockObject(DC_BRUSH));





    
    // �ֻ��� ����
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

    // �ֻ��� ���Ź�ư �ٱ� ( ��ư ��ü )
    Purchase.DrawObject(hdc);

    // �ֻ��� ���Ź�ư ����
    SetDCColor(hdc, RGB(220, 220, 220), RGB(210, 210, 210));
    Ellipse(hdc, 315, 460, 395, 540);

    // ���Ź�ư�� �ֻ���
    SetDCColor(hdc, RGB(255, 255, 255), RGB(1, 1, 1));
    Rectangle(hdc, 340, 465, 370, 495);
    // ���Ź�ư �ֻ��� ��
    SetDCColor(hdc, RGB(0, 0, 0), NULL);
    Ellipse(hdc, 345, 470, 350, 475);
    Ellipse(hdc, 360, 470, 365, 475);
    Ellipse(hdc, 345, 485, 350, 490);
    Ellipse(hdc, 360, 485, 365, 490);


    // �ֻ��� ��ȭ �����̳�
    SetDCColor(hdc, RGB(220, 220, 220), NULL);
    RoundRect(hdc, 135, 575, 575, 680, 20, 20);

    
    // ���� 
    auto it = l_Monster.rbegin();
    while (it != l_Monster.rend())                   // ���� ��ȯ�� ���Ͱ� ��ģ ������ �Ǿտ� ��ġ
    {
        if ((*it)->GetStatus() != STATUS::ALIVE)         // ������� ������
        {
            l_Monster.erase(std::next(it).base());   // ����Ʈ���� ����
            continue;
        }
        (*it)->DrawObject(hdc);
        it++;
    }


    //�ֻ���
    for (int i = 0; i < 15; i++)
    {
        if (v_Dice[i] == nullptr) continue;
        v_Dice[i]->DrawObject(hdc);
    }

    for (auto it = l_Projectile.begin(); it != l_Projectile.end(); it++)
    {

    }
    
    // �巡������ �ӽ� �ֻ���
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

void GameHandler::OnMouseClicked(int x, int y)  // WM_LBUTTONDOWN ���� ȣ��
{
    
    for (int i = 0; i < (int)v_Button.size(); i++)   
    {
        if (v_Button[i].IsOverlappedPoint(x, y))     // Ŭ���� ��ġ�� ��ư�� ���� ���� ������� ��
        {
            v_Button[i].OnClickedObject(g_hWnd);       // ��ư�� ����� �Լ��� ����
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (v_Dice[i] == nullptr) continue;
        if (v_Dice[i]->IsOverlappedPoint({ x,y }))      // Ŭ���� ��ġ�� �ֻ����� ���� ���� ������� ��
        {
            if (bDragging == FALSE)                    // ���� �巡������ �ƴ϶��
            {
                DraggedDice = v_Dice[i].get();             // ���� ��ü �ּ� ����, ������ü�� ������ ����

                DraggingDice = make_unique<DiceBase>(*DraggedDice);     // ����Ʈ ������ �̿��Ͽ� Ŭ���� ���̽��� ���� ���� / ���콺�� �巡��Ǵ� ��ü
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

void GameHandler::OnMouseReleased(int x, int y)  // WM_LBUTTONUP ���� ȣ��
{
    if (IsDragging() == TRUE)       // �巡�����̿��ٸ�
    {


        // ���̽������� ��ħ�� ������� ����Ǵ� �κ�. �巡�׸� �����

        bDragging = FALSE;                          // �巡�� ����
        DraggingDice.reset(nullptr);                // ���콺�� ����ٴϴ� �ӽ� ��ü�� delete�ϰ� ������ nullptr�� ����

        DraggedDice->SetSelected(FALSE);            // ���� ��������
        

        if (DraggedDice->GetEye() < 6)        // ���� 6������ �ֻ��� �϶�
        {

            for (int i = 0; i < 15; i++)     // ��� �ֻ��� Ž��
            {

                if (v_Dice[i] == nullptr) continue;
                if (v_Dice[i]->IsOverlappedPoint({ x,y }))      // ���콺�� ������ ��ġ�� �ֻ����� ��ģ�ٸ�
                {
                    if (*v_Dice[i] == *DraggedDice)          // Ÿ�԰� �ֻ��� ���� ���� ���� ���
                    {
                        if (v_Dice[i].get() == DraggedDice) continue;     // �ڱ� �ڽ��� ����
                        v_Dice[i]->AddEye(1);                // ���� ������Ŵ

                        int temp = DraggedDice->GetSlot();
                        v_Dice[temp].reset();
                        DraggedDice = nullptr;                     // �巡�����̴� �ֻ��� ����
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

// ���͸��� ������ �ο�
DWORD WINAPI MonsterTr(LPVOID Param)
{
   MonsterBase* Monster = (MonsterBase*)Param;
   while (1)
    {
        BOOL bMoveEnd = Monster->MoveNextPoint();   // ���� �̵�. ���� �� ������ �����ϸ� TRUE ��ȯ
        
        if (bMoveEnd) break;

       Sleep(17);
    }
    Monster->SetStatus(STATUS::ARRIVAL);
    ExitThread(0);
    return 0;
}

// �ʴ� 100�� InvalidateRect ȣ��
DWORD WINAPI IDRTimer(LPVOID Param)
{
    while (1) 
    {
        InvalidateRect(g_hWnd, NULL, FALSE);
        Sleep(10);
    }
    ExitThread(0);
    return 0;
}

// ����ü ������
DWORD WINAPI ProjectileTr(LPVOID Param)
{
    ProjectileBase* Projectile = ((pair<ProjectileBase*, MonsterBase*>*)Param)->first;
    MonsterBase* Target = ((pair<ProjectileBase*, MonsterBase*>*)Param)->second;
    if (Projectile == nullptr || Target == nullptr)
    {
        ExitThread(0);
        return 0;
    }


    while (1) 
    {
        BOOL result = Projectile->MoveToTarget(Target); // �̵� ��  Ÿ�ٰ� ��ĥ��� �������� �� ��, TRUE ��ȯ
                                                        // Ÿ���� ������ nullptr�� �� �� ����
        if (result)
        {
            ExitThread(0);
            return 0;
        }
        else 
        Sleep(100);
    }
    return 0;
}