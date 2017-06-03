// Guess_Flag.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Guess_Flag.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING 100
#define RESULT_SIZE 255

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GUESS_FLAG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESS_FLAG));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESS_FLAG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GUESS_FLAG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 50, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	case WM_TIMER:
	{
		switch (wParam)
		{
		case ID_10SECONDS:
		{
			WCHAR *buffer, *temp;
			buffer = new WCHAR[255];
			temp = new WCHAR[10];
			wcscpy(buffer, L"Time up, you have ");
			swprintf(temp, 10, L"%d", point);
			wcscat(buffer, temp);
			wcscat(buffer, L" points");
			KillTimer(hWnd, TimmerID);
			KillTimer(hWnd, TimmerID1);
			MessageBox(NULL,
				buffer,
				(LPCWSTR)L"Game over",
				MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
			);
			PostQuitMessage(0);
			break;
		}
		case ID_1SECONDS:
			timer--;
			WCHAR *temp2;
			temp2 = new WCHAR[5];
			swprintf(temp2, 5, L"%d", timer);
			SetWindowText(timer_hwnd, temp2);
			break;
		}
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	return 0;
	}
}

// Message handler for about box.
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

void Read_Ini_File()
{
	const int BUFFERSIZE = 260;
	WCHAR buffer[BUFFERSIZE];
	WCHAR curPath[BUFFERSIZE];
	WCHAR configPath[BUFFERSIZE];
	WCHAR number_buffer[BUFFERSIZE];
	WCHAR temp[5];
	GetCurrentDirectory(BUFFERSIZE, curPath);
	wsprintf(configPath, L"%s\\config.ini", curPath);
	GetPrivateProfileString(L"app", L"Flag_Number", L"Default value", buffer, BUFFERSIZE, configPath);
	NUMBER_OF_FLAG = _wtof(buffer);
	for (int j = 0; j < NUMBER_OF_FLAG + 1; j++)
	{
		flagname[j] = new WCHAR[30];
	}
	for (int i = 1; i < NUMBER_OF_FLAG + 1; i++)
	{
		wcscpy(number_buffer, L"flag_name");
		swprintf(temp, 5, L"%d", i);
		wcscat(number_buffer, temp);
		GetPrivateProfileString(L"app", number_buffer, L"Default value", buffer, BUFFERSIZE, configPath);
		wcscpy(flagname[i], buffer);
	}
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	HFONT mFont = CreateFont(-35, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT pFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"GUESS FLAG", WS_CHILD | WS_VISIBLE | SS_CENTER, 200, 30, 300, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	start_hwnd = CreateWindowEx(0, L"BUTTON", L"START", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 250, 250, 100, hWnd, (HMENU)IDC_BUTTON0, hInst, NULL);
	SendMessage(start_hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	intro_hwnd = CreateWindowEx(0, L"STATIC", L"There are 196 countries in the world. Can you remember their flags? This app can help you", 
	WS_CHILD | WS_VISIBLE | SS_CENTER, 60, 100, 650, 40, hWnd, NULL, hInst, NULL);
	SendMessage(intro_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	
	return true;
}

void Create_All(HWND hWnd)
{
	DestroyWindow(start_hwnd);
	DestroyWindow(intro_hwnd);
	Read_Ini_File();
	
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	HFONT pFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT mFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	Init_Random_Flag();
	Init_Random_Result(level);
	point = 0;

	WCHAR buffer[255], result[5];
	swprintf(result, 5, L"%d", flag_result[level]);
	wcscpy(buffer, L"./Flag/");
	wcscat(buffer, result);
	wcscat(buffer, L".bmp");
	HWND hwnd;
	hwnd = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_CENTER, 650, 30, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	point_hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER, 650, 70, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(point_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	a_hwnd = CreateWindowEx(0, L"BUTTON", flagname[a], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(a_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	b_hwnd = CreateWindowEx(0, L"BUTTON", flagname[b], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
	SendMessage(b_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	c_hwnd = CreateWindowEx(0, L"BUTTON", flagname[c], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 370, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
	SendMessage(c_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	d_hwnd = CreateWindowEx(0, L"BUTTON", flagname[d], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 530, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON4, hInst, NULL);
	SendMessage(d_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	MyHBitmap = (HBITMAP)::LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_hwnd = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_BITMAP, 130, 110, 400, 200, hWnd, NULL, hInst, NULL);
	SendMessage(bitmap_hwnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)MyHBitmap);
	timer_hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 600, 200, 50, 60, hWnd, NULL, hInst, NULL);
	SendMessage(timer_hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	TimmerID = SetTimer(hWnd, ID_10SECONDS, 11 * 1000, NULL);
	TimmerID = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
}

void Display_Countdown_Timer()
{
	WCHAR *temp;
	temp = new WCHAR[5];
	swprintf(temp, 5, L"%d", timer);
	SetWindowText(timer_hwnd, temp);
}

void Destroy_All()
{
	DestroyWindow(a_hwnd);
	DestroyWindow(b_hwnd);
	DestroyWindow(c_hwnd);
	DestroyWindow(d_hwnd);
	DestroyWindow(bitmap_hwnd);
}

bool Contains(const std::vector<int> &list, int x)
{
	return std::find(list.begin(), list.end(), x) != list.end();
}

void Init_Random_Result(int i)
{
	srand(time(NULL));
	random_result = rand() % 4;
	switch (random_result)
	{
	case 0:
		a = flag_result[i];
		RandomResult(b, c, d, a);
		break;
	case 1:
		b = flag_result[i];
		RandomResult(a, c, d, b);
		break;
	case 2:
		c = flag_result[i];
		RandomResult(a, b, d, c);
		break;
	case 3:
		d = flag_result[i];
		RandomResult(a, b, c, d);
		break;
	}
}

void Init_Random_Flag()
{
	srand(time(NULL));
	int a_z = rand() % NUMBER_OF_FLAG + 1;
	static vector<int> generatedValues;
	generatedValues.push_back(a_z);
	flag_result[1] = a_z;
	for (int j = 2; j < NUMBER_OF_FLAG + 1; j++)
	{
		while (Contains(generatedValues, a_z))
		{
			a_z = rand() % NUMBER_OF_FLAG + 1;
		}
		generatedValues.push_back(a_z);
		flag_result[j] = a_z;
	}
}

void RandomResult(int &a, int &b, int &c, int result)
{
	a = rand() % NUMBER_OF_FLAG+1;
	while (a == result)
	{
		a = rand() % NUMBER_OF_FLAG+1;
	}
	b = rand() % NUMBER_OF_FLAG + 1;
	while (b == a || b == result)
	{
		b = rand() % NUMBER_OF_FLAG + 1;
	}
	c = rand() % NUMBER_OF_FLAG + 1;
	while (c == a || c == b || c == result)
	{
		c = rand() % NUMBER_OF_FLAG + 1;
	}
}

void Update_Point()
{
	WCHAR buffer_point[5];
	swprintf(buffer_point, 5, L"%d", point);
	SetWindowText(point_hwnd, buffer_point);
}

void Check_Answer_And_Reload(HWND hWnd)
{
	KillTimer(hWnd, TimmerID);
	KillTimer(hWnd, TimmerID1);
	HFONT pFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	point += 100;
	level++;
	Update_Point();
	if (level <= NUMBER_OF_FLAG)
	{
		WCHAR buffer[255], result[5];
		swprintf(result, 5, L"%d", flag_result[level]);
		wcscpy(buffer, L"./Flag/");
		wcscat(buffer, result);
		wcscat(buffer, L".bmp");
		MyHBitmap = (HBITMAP)::LoadImage(NULL, buffer, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		DestroyWindow(bitmap_hwnd);
		bitmap_hwnd = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_BITMAP, 130, 120, 400, 200, hWnd, NULL, hInst, NULL);
		SendMessage(bitmap_hwnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)MyHBitmap);
		Init_Random_Result(level);
		DestroyWindow(a_hwnd);
		DestroyWindow(b_hwnd);
		DestroyWindow(c_hwnd);
		DestroyWindow(d_hwnd);
		a_hwnd = CreateWindowEx(0, L"BUTTON", flagname[a], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
		SendMessage(a_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
		b_hwnd = CreateWindowEx(0, L"BUTTON", flagname[b], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
		SendMessage(b_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
		c_hwnd = CreateWindowEx(0, L"BUTTON", flagname[c], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 370, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
		SendMessage(c_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
		d_hwnd = CreateWindowEx(0, L"BUTTON", flagname[d], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 530, 400, 150, 40, hWnd, (HMENU)IDC_BUTTON4, hInst, NULL);
		SendMessage(d_hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
		TimmerID = SetTimer(hWnd, ID_10SECONDS, 11 * 1000, NULL);
		TimmerID1 = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
		timer = 10;
		Display_Countdown_Timer();
	}
	else
	{
		MessageBox(NULL, (LPCWSTR)L"Completed",
			(LPCWSTR)L"Congratulation",
			MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);
	}
}

void Show_Message_Wrong()
{
	MessageBox(NULL, (LPCWSTR)L"-100 points",
		(LPCWSTR)L"Wrong",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);
}

void Wrong_Answer(HWND hWnd)
{
	KillTimer(hWnd, TimmerID);
	KillTimer(hWnd, TimmerID1);
	point -= 100;
	Update_Point();
	Show_Message_Wrong();
	timer = 10;
	TimmerID = SetTimer(hWnd, ID_10SECONDS, 10 * 1000, NULL);
	TimmerID1 = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
	Display_Countdown_Timer();
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		for (int i = 0; i < NUMBER_OF_FLAG + 1; i++)
		{
			delete[]flagname;
		}
		DestroyWindow(hWnd);
		break;
	case IDC_BUTTON0:
		Create_All(hWnd);
		Display_Countdown_Timer();
		break;
	case IDC_BUTTON1:
		if (random_result == 0)
		{
			Check_Answer_And_Reload(hWnd);
		}
		else
		{
			Wrong_Answer(hWnd);
		}
		break;
	case IDC_BUTTON2:
		if (random_result == 1)
		{
			Check_Answer_And_Reload(hWnd);
		}
		else
		{
			Wrong_Answer(hWnd);
		}
		break;
	case IDC_BUTTON3:
		if (random_result == 2)
		{
			Check_Answer_And_Reload(hWnd);
		}
		else
		{
			Wrong_Answer(hWnd);
		}
		break;
	case IDC_BUTTON4:
		if (random_result == 3)
		{
			Check_Answer_And_Reload(hWnd);
		}
		else
		{
			Wrong_Answer(hWnd);
		}
		break;
	}
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}