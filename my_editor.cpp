#include "Lab5.h"
#include "my_editor.h"
#include <commctrl.h>
#include <typeinfo>
#include <string>

#define MY_SHAPE_ARRAY_SIZE 116

MyEditor& MyEditor::getInstance() {
	static MyEditor instance;
	return instance;
}

MyEditor::MyEditor(void)
{
	pTempShape = nullptr;
	buttonId = 0;

	selectedShape = -1;

	isLBdown = FALSE;
	start = {};
	end = {};

}

MyEditor::~MyEditor()
{
	for (auto& shape : pShapes)
		delete shape;
}

void MyEditor::Start(Shape* shape, INT wmId)
{
	if (pTempShape)
		delete pTempShape;
	pTempShape = shape;
	buttonId = wmId;

	tbm.CheckButton(buttonId);
}

BOOL MyEditor::GetShape(INT i, std::wstring* name, RECT* shape)
{
	if (pShapes.size() < i || i < 0)
		return FALSE;

	LPCSTR shapeName = typeid(*pShapes[i]).name();
	LPWSTR wshapename = new WCHAR[strlen(shapeName)];
	MultiByteToWideChar(CP_ACP, 0, shapeName + 6, -1, wshapename, (int)strlen(shapeName));
	*name = std::wstring(wshapename);
	delete[] wshapename;

	*shape = pShapes[i]->Get();
	return TRUE;
}

BOOL MyEditor::AddShape(Shape* shape, RECT coords)
{
	if (pShapes.size() >= MY_SHAPE_ARRAY_SIZE)
		return FALSE;

	shape->Set(coords.left, coords.top, coords.right, coords.bottom);
	pShapes.push_back(shape->Clone());

	return TRUE;
}

BOOL MyEditor::DelShape(INT i)
{
	if (pShapes.size() < i || i < 0)
		return FALSE;

	if (i == selectedShape)
		SelectShape(-1);
	else if (i < selectedShape)
		SelectShape(selectedShape  - 1);

	pShapes.erase(pShapes.begin() + i);
	return TRUE;
}

BOOL MyEditor::ShowShape(INT i, HDC hdc)
{
	if (pShapes.size() < i || i < 0)
		return FALSE;

	pShapes[i]->Show(hdc);
	return TRUE;
}

BOOL MyEditor::SelectShape(INT i)
{
	if (pShapes.size() < i || i < 0)
		selectedShape = -1;

	selectedShape = i;
	return TRUE;
}

void MyEditor::ShapeAdded(std::function<void(std::wstring, RECT)> func)
{
	listeners.push_back(func);
}


void MyEditor::OnLBdown(HWND hWnd)
{
	if (!pTempShape) return;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	start.x = end.x = pt.x;
	start.y = end.y = pt.y;

	isLBdown = TRUE;
}

void MyEditor::OnLBup(HWND hWnd)
{
	if (!pTempShape) return;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	end.x = pt.x;
	end.y = pt.y;

	isLBdown = FALSE;

	InvalidateRect(hWnd, NULL, TRUE);
	if (!AddShape(pTempShape, RECT{ start.x, start.y, end.x, end.y }))
		return;

	std::wstring newName;
	RECT newShape;
	GetShape(pShapes.size() - 1, &newName, &newShape);
	for (auto& func : listeners)
		func(newName, newShape);
}

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (!isLBdown) return;

	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, 0);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	pTempShape->Set(start.x, start.y, end.x, end.y);
	pTempShape->ShowPreview(hdc);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	end.x = pt.x;
	end.y = pt.y;
	pTempShape->Set(start.x, start.y, end.x, end.y);
	pTempShape->ShowPreview(hdc);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void MyEditor::OnPaint(HWND hWnd, HDC hdc)
{
	for (int i = 0; i < pShapes.size(); i++)
		ShowShape(i, hdc);

	HPEN hPenOld, hPen;
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	ShowShape(selectedShape, hdc);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);

	if (!(pTempShape && (HMENU)wParam == hSubMenu))
		return;

	int lastIndex = GetMenuItemCount(hSubMenu) - 1;

	MENUITEMINFO mii{ sizeof(mii), MIIM_ID };

	for (int i = 0; i <= lastIndex; i++)
	{
		GetMenuItemInfo(hSubMenu, i, TRUE, &mii);
		if (mii.wID == buttonId)
			CheckMenuRadioItem(hSubMenu, 0, lastIndex, i, MF_BYPOSITION);
	}
}

void MyEditor::OnCreate(HWND hWnd)
{
	tbm.OnCreate(hWnd);
}
void MyEditor::OnSize(HWND hWnd)
{
	tbm.OnSize(hWnd);
}
void MyEditor::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	tbm.OnNotify(hWnd, wParam, lParam);
}