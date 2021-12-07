﻿// 201807027이태양.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "201807027이태양.h"
#include "GameHandler.h"
#include "iostream"
#include <stdio.h>
#include <cstring>

#define MAX_LOADSTRING 100

#define DEBUG_MODE false


#if DEBUG_MODE
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")     // 디버그용 콘솔 출력
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI IDRTimer(LPVOID Param);

// 사용자 제작 함수
void                OnPaint(HWND hWnd);         // WM_PAINT 발생시 호출. WM_PAINT의 역할을 함

// 전역변수
GameHandler *GHnd;                               // 게임 핸들러

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY201807027, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201807027));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201807027));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY201807027);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
      CW_USEDEFAULT, 0, 740, 780, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

HWND g_hWnd;
HANDLE IDRHandle;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        
    case WM_MOUSEMOVE:
    {
        GHnd->SetMousePos(LOWORD(lParam), HIWORD(lParam));
        
        if (DEBUG_MODE)
        {
            //cout << "x : " << LOWORD(lParam) << "     y : " << HIWORD(lParam) << endl;
        }
        if (GHnd->IsDragging())
        {
            GHnd->OnMouseMoved();
        }
    }
    break;

    case WM_LBUTTONDOWN:
        GHnd->OnMouseClicked(LOWORD(lParam),HIWORD(lParam));
        break;
    case WM_LBUTTONUP:
        GHnd->OnMouseReleased(LOWORD(lParam), HIWORD(lParam));
    case WM_PAINT:


        OnPaint(hWnd);
        break;
    case WM_DESTROY:
        GHnd->DestroyInst();
        SuspendThread(IDRHandle);
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        g_hWnd = hWnd;
        IDRHandle = CreateThread(NULL, 0, IDRTimer, NULL, 0, NULL);

        GHnd = GameHandler::GetInstance();
        GHnd->SetHWND(hWnd);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;

    static HDC hdc, MemDC;                                                     
    static HBITMAP BackBit, oldBackBit;
    static RECT bufferRT;
    MemDC = BeginPaint(hWnd, &ps);                                              // 더블버퍼링 == OnPaint가 불릴때마다 흰색 화면에다 새로 그리는것이 아닌 미리 다른데다가 그려놓고 옮기는것

    GetClientRect(hWnd, &bufferRT);                                             // hWnd RECT를 가져옴
    hdc = CreateCompatibleDC(MemDC);                                            // 화면에 출력하지 않는 DC를 가져옴
    BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);   // MemDC와 호환되는 Bitmap을 만듬 == 메인 화면의 정보와 똑같은 그림판을 만듬
    oldBackBit = (HBITMAP)SelectObject(hdc, BackBit);                           // 그림판과 hdc를 연결 == hdc로 그림을 그려도 출력되지 않고 BackBit에 그려짐
    PatBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);              // 흰바탕 그림


    // 실제 그리기 코드


    GHnd->DrawGame(hdc);

    // 더블버퍼링 끝
    GetClientRect(hWnd, &bufferRT);                                             // hWnd RECT를 가져옴
    BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hdc, 0, 0, SRCCOPY);   // hdc로 그렸던 그림들을 MemDC에다가 그림
    SelectObject(hdc, oldBackBit);                                              // hdc가 이전 비트맵을 선택하도록 함
    DeleteObject(BackBit);
    DeleteDC(hdc);
    EndPaint(hWnd, &ps);
    
}
// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 초당 100번 InvalidateRect 호출
DWORD WINAPI IDRTimer(LPVOID Param)
{
    while (1)
    {
        InvalidateRect(g_hWnd, NULL, FALSE);
        Sleep(10);
    }
    return 0;
}
