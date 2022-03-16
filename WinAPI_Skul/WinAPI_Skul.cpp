﻿// WinAPI_Skul.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WinAPI_Skul.h"
#include "locale.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE   hInst;                                // 현재 인스턴스입니다.
HWND        hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 실행된 프로세스의 시작 주소
    _In_opt_ HINSTANCE hPrevInstance, // 이전에 실행된 인스턴스 값
    _In_ LPWSTR    lpCmdLine, // 명령으로 입력된 프로그램의 인수
    _In_ int       nCmdShow) // 프로그램이 시작될 형태
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    //ShowCursor(false);

    // 해당 지역으로 설정
    setlocale(LC_ALL, "Korean");

    // 메모리 릭 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(268);

    // 전역 문자열을 초기화합니다.
    // 리소스 뷰의 String Table에서 ID값으로 String을 가져오는 함수
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // 프로그램 타이틀을 불러옴.
    LoadStringW(hInstance, IDC_WINAPISKUL, szWindowClass, MAX_LOADSTRING); // 프로그램 클래스를 불러옴.

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 초기화
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    CCore::GetInst()->Init();

    // 단축키 정보를 불러온다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPISKUL));


    // 기본 메시지 루프입니다:
    // 메세지 큐에서 메세지가 확인될 때까지 대기
    // 메세지 큐에 msg.message == WM_QUIT 인 경우 false를 반환

    // GetMessage : 메시지 큐에 메시지가 없다면 대기, 메시지가 들어온다면 true 반환
    // PeekMessage : 메시지 큐에 메시지가 없다면 false 반환, 메시지가 있다면 true 반환

    // 게임 루프
    // 이전 GetMessage의 대기 상태 유지에서
    // 현재 PeekMessage의 메시지가 없는 상황(대부분)에서 게임 상황 처리
    MSG msg;
    while (TRUE)
    {
        // PM_REMOVE를 통해 확인한 메세지를 제거한다.
        // 메세지에 대한 처리는 보통 금방 처리되기에 게임 연산에 지장이 갈 정도는 아니다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키에 대한 처리
            {
                TranslateMessage(&msg);     // 키보드 입력메세지 처리를 담당
                DispatchMessage(&msg);      // WndProc에서 전달된 메세지를 실제 윈도우에 전달
            }
        }
        // 메세지가 없을 때 게임에 대한 처리를 진행한다.
        else
        {
            // 게임 로직
            // 게임 업데이트와 게임 렌더
            CCore::GetInst()->Update();
            CCore::GetInst()->Render();
        }

    }
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우 창의 정보를 저장하기 위한 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기 설정

    wcex.style = CS_HREDRAW | CS_VREDRAW;           // 윈도우 클래스의 스타일 지정
    wcex.lpfnWndProc = WndProc;                     // 윈도우의 메세지를 처리하는 함수 WndProc 지정
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;                     // 인스턴스 핸들러 지정
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WINAPISKUL));      // 아이콘 지정
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);                      // 커서 지정
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                    // 바탕화면 지정
    wcex.lpszMenuName = nullptr;                                        // 메뉴 옵션 지정
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 스몰 아이콘 지정

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
    // 프로그램에 대한 주소값
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 윈도우 창에 대한 주소값
    hWnd = CreateWindowW(szWindowClass,         // 클래스 이름
        szTitle,               // 윈도우 이름
        WINSTYLE,              // 윈도우 스타일
        WINSTARTX,             // 윈도우 시작 X
        WINSTARTY,             // 윈도우 시작 Y
        WINSIZEX,              // 윈도우 가로 크기
        WINSIZEY,              // 윈도우 세로 크기
        nullptr,               // 부모 윈도우
        nullptr,               // 메뉴 핸들
        hInstance,             // 프로세스 인스턴스의 핸들
        nullptr);              // 추가 매개변수

    if (!hWnd)
    {
        return FALSE;
    }

    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = WINSIZEX;
    rc.bottom = WINSIZEY;
    // 실제 내용 창이 크기에 맞게끔 하도록 사이즈.
    AdjustWindowRect(&rc, WINSTYLE, false);
    // 위에서 얻은 사이즈로 윈도우 사이즈를 세팅하자.
    SetWindowPos(hWnd, NULL, WINSTARTX, WINSTARTY,
        (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

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

POINT g_mousePos = { 0,0 };
POINT g_mouseStartPos = { 0,0 };
POINT g_mouseEndPos = { 0,0 };
POINT g_keyPos = { 0, 0 };
bool isClick = false;

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
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    break;
    case WM_KEYDOWN:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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