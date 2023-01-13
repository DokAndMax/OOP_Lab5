#pragma once
#include "framework.h"
#include "shape.h"

class ToolbarManager
{
private:
	HWND hwndToolBar;
public:
	ToolbarManager(void);
	HWND OnCreate(HWND);
	void OnSize(HWND);
	void OnNotify(HWND, WPARAM, LPARAM);
	void CheckButton(LPARAM);
};