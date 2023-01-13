#include "toolbar_manager.h"
#include <commctrl.h>
#include "framework.h"
#include "Lab5.h"
#include "my_table.rh"

ToolbarManager::ToolbarManager(void)
{
	hwndToolBar = NULL;
}

HWND ToolbarManager::OnCreate(HWND hWnd)
{
	TBBUTTON tbb[8]; //��� Toolbar � ������� ��������
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = BTNS_CHECKGROUP;
	tbb[0].idCommand = IDM_POINT;

	tbb[1].iBitmap = 1;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = BTNS_CHECKGROUP;
	tbb[1].idCommand = IDM_LINE;

	tbb[2].iBitmap = 2;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = BTNS_CHECKGROUP;
	tbb[2].idCommand = IDM_RECT;

	tbb[3].iBitmap = 3;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = BTNS_CHECKGROUP;
	tbb[3].idCommand = IDM_ELLIPSE;

	tbb[4].iBitmap = 4;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = BTNS_CHECKGROUP;
	tbb[4].idCommand = IDM_LINEOO;

	tbb[5].iBitmap = 5;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = BTNS_CHECKGROUP;
	tbb[5].idCommand = IDM_CUBE;

	tbb[6].iBitmap = 0;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_SEP;
	tbb[6].idCommand = 0;

	tbb[7].iBitmap = 6;
	tbb[7].fsState = TBSTATE_ENABLED;
	tbb[7].fsStyle = BTNS_BUTTON;
	tbb[7].idCommand = IDD_DIALOG1;

	hwndToolBar = CreateToolbarEx(hWnd, //���������� ����
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP |
		TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS,
		IDC_MY_TOOLBAR, //ID ���������� ���� Toolbar
		7,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		IDB_TOOLBAR,
		tbb, //����� ����� ������
		8, //������� ������
		24, 24, 24, 24, //������������ �� ������
		sizeof(TBBUTTON));
	return hwndToolBar;
}


//---�������� ����������� WM_SIZE---
void ToolbarManager::OnSize(HWND hWnd)
{
	if (!hwndToolBar)
		return;

	RECT rc, rw;
	GetClientRect(hWnd, &rc); //��� ������ ��������� ����
	GetWindowRect(hwndToolBar, &rw); //��� ������� ����� ������ Toolbar
	MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
}

void ToolbarManager::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR pnmh = (LPNMHDR)lParam;
	if (pnmh->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
		switch (lpttt->hdr.idFrom)
		{
		case IDM_POINT:
			lstrcpy(lpttt->szText, L"�����");
			break;
		case IDM_LINE:
			lstrcpy(lpttt->szText, L"˳��");
			break;
		case IDM_RECT:
			lstrcpy(lpttt->szText, L"�����������");
			break;
		case IDM_ELLIPSE:
			lstrcpy(lpttt->szText, L"����");
			break;
		case IDM_LINEOO:
			lstrcpy(lpttt->szText, L"˳�� � ������� �� �����");
			break;
		case IDM_CUBE:
			lstrcpy(lpttt->szText, L"���");
			break;
		case IDD_DIALOG1:
			lstrcpy(lpttt->szText, L"������ �����");
			break;
		default: lstrcpy(lpttt->szText, L"���� �������");
		}
	}
}

void ToolbarManager::CheckButton(LPARAM idButton)
{
	if (!hwndToolBar)
		return;

	SendMessage(hwndToolBar, TB_CHECKBUTTON, idButton, TRUE);
}
