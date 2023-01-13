#pragma once
#include "framework.h"
#include "resource.h"

//---оголошення класу---
class Shape
{
protected:
	RECT shape;
public:
	virtual ~Shape();
	void Set(long x1, long y1, long x2, long y2);
	RECT Get();
	virtual void Show(HDC) = 0;
	virtual void ShowPreview(HDC);
	virtual Shape* Clone() = 0;
};