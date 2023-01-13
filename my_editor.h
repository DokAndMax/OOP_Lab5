#pragma once
#include "shape.h"
#include "toolbar_manager.h"
#include <vector>
#include <list>
#include <string>
#include <functional>

class MyEditor
{
private:
	MyEditor();
	MyEditor(const MyEditor&);
	MyEditor& operator=(MyEditor&);

	std::vector<Shape*> pShapes;

	Shape* pTempShape;
	INT buttonId;

	std::list<std::function<void(std::wstring, RECT)>> listeners;
	INT selectedShape;

	ToolbarManager tbm;

	BOOL isLBdown;
	POINT start;
	POINT end;

public:
	static MyEditor& getInstance();
	~MyEditor();
	void Start(Shape*, INT);

	BOOL GetShape(INT, std::wstring*, RECT*);
	BOOL AddShape(Shape*, RECT);
	BOOL DelShape(INT);
	BOOL ShowShape(INT, HDC);
	BOOL SelectShape(INT);

	void ShapeAdded(std::function<void(std::wstring, RECT)>);

	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	void OnInitMenuPopup(HWND, WPARAM);

	void OnCreate(HWND);
	void OnSize(HWND);
	void OnNotify(HWND, WPARAM, LPARAM);
};