#pragma once

#include "resource.h"
#include <windowsx.h>
#include <winuser.h>
#include <commctrl.h>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void RandomResult(int &a, int &b, int &c, int result);
void Check_Answer_And_Reload(HWND hWnd);
void Create_All(HWND hWnd);
void Update_Point();
void Init_Random_Flag();
void Init_Random_Result(int i);
void Read_Ini_File();
void Show_Message_Wrong();
void Wrong_Answer(HWND hWnd);
void Destroy_All();
void Display_Countdown_Timer();
int point;
int timer = 10;
HWND point_hwnd, a_hwnd, b_hwnd, c_hwnd, d_hwnd, bitmap_hwnd, start_hwnd, intro_hwnd, timer_hwnd;
WCHAR *flagname[255];
int flag_result[255], random_result;
int level = 1;
int NUMBER_OF_FLAG, a, b, c, d = 0;
HBITMAP MyHBitmap;
HDC	localDC;
HBITMAP hOldBitmap;
UINT TimmerID = 0;
UINT TimmerID1 = 1;