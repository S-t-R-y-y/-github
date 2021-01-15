#include "resource.h"
#include<windows.h>
#include<stdlib.h>
#include<tchar.h>
#include<math.h>


#pragma comment(lib, "msimg32.lib")

#define KEYCODE_MAX			256

#define ERR_BITMAP_LOAD_TITLE	TEXT("ビットマップ読込・失敗")
#define ERR_BITMAP_LOAD_TEXT	TEXT("ビットマップを読み込めません。終了します。")

bool IsWindowClassRegi(PCTSTR, HINSTANCE);
void IsWindowCreate(HWND *, PCTSTR, HINSTANCE);
void SetClientSize(HWND);
void CreateDoubleBufferring(HWND);

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

WNDCLASS winc;
HWND hWnd;
MSG msg;
RECT rect_window;
RECT rect_client;
POINT mousePt;
HINSTANCE AppInst;

float fps;
DWORD fps_sta_tm;
DWORD fps_end_tm;
DWORD fps_count;

HBITMAP hbmp_double;
HDC hdc_double;

//---------------------------------------------------------------------

LPCSTR MY_WIN_ICON;
TCHAR *MY_WIN_TITLE;
int MY_WINDOW_WIDTH = 0;
int MY_WINDOW_HEIGHT = 0;

int ChangeWindowMode(int flag);
int SetGraphMode(int ScreenSizeX, int ScreenSizeY, int Color);
int SetWindowStyleMode(int Mode);
int SetMainWindowText(const TCHAR* WindowText);
int SetWindowIconID(int ID);
int SetMouseDispFlag(int flag);
int SetDrawScreen(int DrawScreen);
HWND GetMainWindowHandle(void);
int ProcessMessage(void);
int ClearDrawScreen(void);
int ScreenFlip(void);
int GetNowCount(void);
int WaitTimer(int WaitTime);
int GetHitKeyStateAll(char *KeyStateArray);
int GetMousePoint(int *XBuff,int *YBuff);
int GetMouseInput(void);
int GetMouseWheelRotVol(void);
int CheckSoundMem(int SoundHandle);
int ChangeVolumeSoundMem(int Volume, int SoundHandle);
int PlaySoundMem(int SoundHandle, int PlayType);
int StopSoundMem(int SoundHandle);
int SetMousePoint(int PointX, int PointY);
int DrawGraph(int x, int y, int GrHandle, int TransFlag);
int DrawRotaGraph(int x, int y, double ExRate, double Angle, int grHandle, int TransFlag);
int SetDrawBlendMode(int BlendMode, int BlendParam);
int DrawBox(int x1,int y1,int x2,int y2,unsigned int Color, int FillFlag);
//---------------------------------------------------------------------

bool IsWindowClassRegi(PCTSTR wndclass, HINSTANCE inst)
{
	winc.style =
		CS_HREDRAW
		| CS_VREDRAW;
	//|CS_NOCLOSEs
	winc.lpfnWndProc = WinProc;
	winc.cbClsExtra = 0;
	winc.cbWndExtra = 0;
	winc.hInstance = inst;
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hIcon = LoadIcon(inst, MY_WIN_ICON);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = wndclass;

	if (!RegisterClass(&winc))
	{
		return(FALSE);
	}

	return(TRUE);
}

void IsWindowCreate(HWND *wnd, PCTSTR wndclass, HINSTANCE inst)
{
	*(wnd) = CreateWindowEx(
		WS_EX_LEFT,
		wndclass,
		MY_WIN_TITLE,
		WS_CAPTION
		| WS_SYSMENU
		| WS_MINIMIZEBOX
		//| WS_MAXIMIZEBOX
		//| WS_THICKFRAME
		| WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		MY_WINDOW_WIDTH,
		MY_WINDOW_HEIGHT,
		NULL,
		NULL,
		inst,
		NULL
	);

	return;
}

void SetClientSize(HWND hWnd)
{
	RECT rect_set;

	rect_set.top = 0;
	rect_set.left = 0;
	rect_set.right = MY_WINDOW_WIDTH;
	rect_set.bottom = MY_WINDOW_HEIGHT;

	GetWindowRect(hWnd, &rect_window);
	GetClientRect(hWnd, &rect_client);

	int WindowWidth = rect_window.right - rect_window.left;
	int ClientWidth = rect_client.right - rect_client.left;
	int YohakuWidth = WindowWidth - ClientWidth;
	rect_set.right += YohakuWidth;

	int WindowHeight = rect_window.bottom - rect_window.top;
	int ClientHeight = rect_client.bottom - rect_client.top;
	int YohakuHeight = WindowHeight - ClientHeight;
	rect_set.bottom += YohakuHeight;

	SetWindowPos(
		hWnd,
		HWND_TOP,
		rect_set.left,
		rect_set.top,
		rect_set.right,
		rect_set.bottom,
		SWP_SHOWWINDOW);

	GetClientRect(hWnd, &rect_client);

	return;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int retCloseMsg;

	HDC hdc;

	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_CREATE:

		return(0);

	case WM_MOUSEMOVE:
		mousePt.y = HIWORD(lp);
		mousePt.x = LOWORD(lp);

		return(0);

	case WM_LBUTTONDOWN:
		mousePt.y = HIWORD(lp);
		mousePt.x = LOWORD(lp);

		return(0);

	case WM_LBUTTONUP:
		mousePt.y = HIWORD(lp);
		mousePt.x = LOWORD(lp);

		return(0);

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SaveDC(hdc);

		Rectangle(hdc_double, rect_client.left, rect_client.top, rect_client.right, rect_client.bottom);

		BitBlt(hdc, 0, 0, rect_client.right, rect_client.bottom, hdc_double, 0, 0, SRCCOPY);

		RestoreDC(hdc, -1);

		EndPaint(hwnd, &ps);

		return(0);

	case WM_CLOSE:
		retCloseMsg =
			MessageBox(hwnd, TEXT("終了しますか？"), TEXT("Close?"), MB_YESNO | MB_ICONINFORMATION);

		if (retCloseMsg == IDNO)
		{
			return(0);
		}

		break;

	case WM_DESTROY:
		PostQuitMessage(0);

		return(0);

	}
	return(DefWindowProc(hwnd, msg, wp, lp));
}

void CreateDoubleBufferring(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);

	hbmp_double = CreateCompatibleBitmap(hdc, rect_client.right, rect_client.bottom);

	hdc_double = CreateCompatibleDC(hdc);
	SelectObject(hdc_double, hbmp_double);

	ReleaseDC(hWnd, hdc);
	return;
}

/*
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	AppInst = hInstance;

	if (IsWindowClassRegi(MY_WIN_CLASS, hInstance) == FALSE)
	{
		exit(EXIT_FAILURE);
	}

	IsWindowCreate(&hWnd, MY_WIN_CLASS, hInstance);
	if (hWnd == NULL)
	{
		exit(EXIT_FAILURE);
	}

	SetClientSize(hWnd);

	ShowWindow(hWnd, nCmdShow);

	CreateDoubleBufferring(hWnd);

	while(1)if (msg.message == WM_QUIT) { break; };
	DispatchMessage(&msg);
	InvalidateRect(hWnd, NULL, FALSE);
	UpdateWindow(hWnd);
	DestroyWindow(hWnd);
	UnregisterClass(MY_WIN_CLASS, hInstance);
	return(msg.wParam);
}
*/

/*
void MY_UPDATE_KEYDOWN(void)
{
	int checkKey;

	GetKeyboardState(KeyBoard);

	BYTE IskeyDown_W = KeyBoard['W'] & 0x80;
	BYTE IskeyDown_D = KeyBoard['D'] & 0x80;
	BYTE IskeyDown_A = KeyBoard['A'] & 0x80;
	BYTE IskeyDown_S = KeyBoard['S'] & 0x80;

	for (checkKey = 0; checkKey < KEYCODE_MAX; checkKey++)
	{
		if ((KeyBoard[checkKey] & 0x80) != 0)
		{
			KeyDownState[checkKey] = TRUE;
		}
		else
		{
			KeyDownState[checkKey] = FALSE;
		}
	}

	return;
}
*/

/*
				BitBlt(
					hdc,
					(yoko + 0) * BLOCK_WIDTH,
					(tate + 0) * BLOCK_HEIGHT,
					BLOCK_WIDTH,
					BLOCK_HEIGHT,
					block_bmp.mhdc,
					0,
					((int)block[tate][yoko].kind - 1) * BLOCK_HEIGHT,
					SRCCOPY
				);
				*/
/*
bool SetFont(MY_FONT *font, LPCTSTR Name, LPCTSTR str, int size, int angle, int charset, COLORREF Tx, COLORREF Bk, int BkMode)
{
	wsprintf(font->name, Name);
	wsprintf(font->string, str);
	font->size = size;
	font->angle = angle;
	font->charaset = charset;
	font->TxColor = Tx;
	font->BkColor = Bk;
	font->BkMode = BkMode;

	CreateFontHandle(font);

	if (font->handle == NULL)
	{
		return(FALSE);
	}

	font->left = 0;
	font->top = 0;

	return(TRUE);
}

void CreateFontHandle(MY_FONT *font)
{
	font->handle = CreateFont(
		font->size,
		0,
		font->angle,
		0,
		FW_REGULAR,
		FALSE,
		FALSE,
		FALSE,
		font->charaset,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		font->name);

	return;
}


void AtariRectDraw(HDC hdc, RECT rect)
{
	if (ATARI_DEBUG_MODE == TRUE)
	{
		hpen_atari_old
			= (HPEN)SelectObject(hdc, hpen_atari);
		hbr_atari_old
			= (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(hdc, hpen_atari_old);
		SelectObject(hdc, hbr_atari_old);
	}

	return;
}
*/
/*
HBITMAP LoadBitmapAPI(LPCTSTR imagePath)
{
	HBITMAP bmp = (HBITMAP)LoadImage(
		NULL,
		imagePath,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
		| LR_CREATEDIBSECTION);

	return(bmp);
}


void GetSizeBitmap(MY_BITMAP *my_bmp)
{
	GetObject(my_bmp->hbmp, sizeof(BITMAP), &my_bmp->bmp);
	my_bmp->width = my_bmp->bmp.bmWidth;
	my_bmp->height = my_bmp->bmp.bmHeight;

	return;
}
*/