#pragma once
#include "framework.h"
#include <string>
#include <list>
#include <vector>
#include <functional>


class MyTable
{
private:
	struct lvItem {
		std::wstring name;
		RECT shape;
	};
	std::vector<lvItem> items;
	std::list<std::function<void(INT)>> itemActivatedListeners;
	std::list<std::function<void(INT)>> itemDeletedListeners;
	HWND hWndDialog = nullptr;

public:
	HWND Run(HWND);
	void Show(HWND);
	void Save(HWND);
	void Add(std::wstring, RECT); //функція додавання у таблицю нового рядка з описом об’єкту

	void ItemActivated(std::function<void(INT)>);
	void ItemDeleted(std::function<void(INT)>);

	void OnItemActivate(HWND, LPARAM);
	void OnItemDeleted(HWND);
	//інші функції
};

