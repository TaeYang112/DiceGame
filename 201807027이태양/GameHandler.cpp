
#include "GameHandler.h"
#include "resource.h"

GameHandler::GameHandler()
{
    MousePos = { 0,0 };
    newPen = nullptr;
    newBrush = nullptr;
    oldPen = nullptr;
    oldBrush = nullptr;
    
    bUsingBrushPen = false;
}
Point GameHandler::GetMousePos() const
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
    // ���� HINSTANCE
    HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);    

    // ������ �� ������ ���� DC_PEN ���
    oldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));                   
    oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));

    // ���� �׵θ� �׸���
    SetDCColor(hdc, RGB(200,200,200), NULL);
    RoundRect(hdc, 30, 20, 700, 670, 30, 30);              
    ClearDCColor(hdc);  

    // ���� �׵θ�
    RoundRect(hdc, 20, 0, 690, 660, 30, 30);      

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
    newPen = CreatePen(PS_SOLID, 3, RGB(200, 200, 200));    
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

    // �ֻ��� ���Ź�ư �ٱ�
    SetDCColor(hdc, RGB(200, 200, 200), RGB(170, 170, 170));
    Ellipse(hdc, 305, 450, 405, 550);

    // �ֻ��� ���Ź�ư ����
    SetDCColor(hdc, RGB(220, 220, 220), RGB(210, 210, 210));
    Ellipse(hdc, 315, 460, 395, 540);

    // �ֻ��� ���Ź�ư�� �ֻ���
    SetDCColor(hdc, RGB(255, 255, 255), RGB(1, 1, 1));
    Rectangle(hdc, 340, 465, 370, 495);

    SetDCColor(hdc, RGB(0, 0, 0), NULL);
    Ellipse(hdc, 345, 470, 350, 475);
    Ellipse(hdc, 360, 470, 365, 475);
    Ellipse(hdc, 345, 485, 350, 490);
    Ellipse(hdc, 360, 485, 365, 490);

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


/*  ��Ʈ�� ���
    HDC MemDC = CreateCompatibleDC(hdc);
    HBITMAP bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    HBITMAP obit = (HBITMAP)SelectObject(MemDC, bit);

    StretchBlt(hdc, 0, 0, 620, 570, MemDC, 0, 00, 470, 570, SRCCOPY);

    SelectObject(MemDC, obit);
    DeleteObject(bit);
    DeleteDC(MemDC);
*/