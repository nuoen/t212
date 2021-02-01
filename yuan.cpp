#include <windows.h>
#include <strsafe.h>
#define N 10
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindows");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style =CS_HREDRAW| CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Need Windows NT"), TEXT("Error"), MB_OK);
		return 0;
	}
	hwnd = CreateWindow(szAppName, TEXT("WindowsName"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rect;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int xpos;
	static int ypos;
	TCHAR szString1[128]=TEXT("x");
	int i ;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		GetTextMetrics(hdc, &tm);
		SetTextAlign(hdc, GetTextAlign(hdc) | TA_CENTER);
		ypos = tm.tmHeight + tm.tmExternalLeading;
		for ( i = 1; i <= N; i++)
		{
			TextOut(hdc, rect.right/2, rect.bottom/2 -(N/2-i+1)* ypos, szString1, 2 * i-1 );
			StringCchCat(szString1, 2 * i+2 , TEXT("xx"));
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("�Ƿ�Ҫ�ر�"), TEXT("��ʾ"), MB_YESNO) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}