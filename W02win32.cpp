// W02win32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "W02win32.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static int x = -100, y = -100;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//EntryPoint 진입점
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
    LoadStringW(hInstance, IDC_W02WIN32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Accelerators => 핫 키
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_W02WIN32));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_W02WIN32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_W02WIN32);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: //WM : Window message
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
    case WM_LBUTTONDOWN:  //왼쪽 마우스 버튼 누를 때, 윈도우창을 넘기면 그림이 삭제됨.
        { 
            //MessageBox(hWnd, L"마우스", L"버튼 클릭", MB_OK); //MB : Message Box로 확인 버튼, 문자열 넣을 시 대문자L
            
            //int x, y;
            x = LOWORD(lParam);
            y = HIWORD(lParam);


            InvalidateRect(hWnd, NULL, TRUE); //값 변경 후 다시 그리기, invalidate : 비유효하게, 적절하지 않게 만듦 => 작업이 필요한 상태로 만듬 = 다시 그리도록 만듦 => WM_PAINT 호출
            /*
            HDC hdc = GetDC(hWnd);

            HBRUSH yellow, oldBrush; //색 및 색칠.
            yellow = CreateSolidBrush(RGB(255, 255, 0)); // Soild : 꽉 채움, 색깔 및 지역변수 생성.
            oldBrush = (HBRUSH)SelectObject(hdc, yellow); //hdc에 yello를 전달하고 oldBrush에 옛 색을 전달함. select 후에 되돌려줘야 프로그램 메모리 오류 발생하지 않음.

            HPEN blue, oldPen;
            blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); //펜
            oldPen = (HPEN)SelectObject(hdc, blue);
            //----------------------------------------------------------
            //그리기
            //-----------------------------------------------------------
            //Rectangle(hdc, x - 100, y- 100, x + 100, y + 100);
            Ellipse(hdc, x - 50, y - 50, x + 50, y + 50); //장축과 단축의 길이가 같은 타원 = 원.
            //-------------------------------------------------------------
            SelectObject(hdc, oldBrush); //hdc에 옛 색을 되돌려줌.
            DeleteObject(yellow); //색깔 삭제

            SelectObject(hdc, oldPen);
            DeleteObject(blue);
            ReleaseDC(hWnd, hdc); //GetDC 후 무조건 ReleaseDC
            */

            //DOC-Model과 View는 서로 연관되지 않고 각각의 작업을 수행하며 서로 분리됨. 결과적으로 DOC-Model(data)는 연산 후 Controller(중앙 관리)에 전송하여 연산 및 판단 후 View에 전송.
            //따라서 각각의 역할에 따라 DOC-Model은 DOC-model 역할만, View는 View역할만 수행해야하며 DOC-Model에서 View의 역할을 수행하면 안됨. 이는 코드의 재사용 효율을 높임. 이를 MVC라고 불림.
        }
        break;
    case WM_PAINT: //윈도우 창을 넘겨도 그림이 그대로 유지됨.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // h : handle, dc : device context의 약자로 출력할 때 사용.
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            //Rectangle(hdc, 10, 10, 100, 100);

            //HDC hdc = GetDC(hWnd);

            HBRUSH yellow, oldBrush; //색 및 색칠.
            yellow = CreateSolidBrush(RGB(255, 255, 0)); // Soild : 꽉 채움, 색깔 및 지역변수 생성.
            oldBrush = (HBRUSH)SelectObject(hdc, yellow); //hdc에 yello를 전달하고 oldBrush에 옛 색을 전달함. select 후에 되돌려줘야 프로그램 메모리 오류 발생하지 않음.

            HPEN blue, oldPen;
            blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); //펜
            oldPen = (HPEN)SelectObject(hdc, blue);
            //----------------------------------------------------------
            //그리기
            //-----------------------------------------------------------
            //Rectangle(hdc, x - 100, y- 100, x + 100, y + 100);
            Ellipse(hdc, x - 50, y - 50, x + 50, y + 50); //장축과 단축의 길이가 같은 타원 = 원.
            //-------------------------------------------------------------
            SelectObject(hdc, oldBrush); //hdc에 옛 색을 되돌려줌.
            DeleteObject(yellow); //색깔 삭제

            SelectObject(hdc, oldPen);
            DeleteObject(blue);
            //ReleaseDC(hWnd, hdc); //GetDC 후 무조건 ReleaseDC

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

/*
... => 다이얼로그창 발생
*/