#pragma once
#include "shape.h"

class RectShape : public virtual Shape
{
public:
	void Show(HDC hdc);
	void ShowPreview(HDC hdc);
	Shape* Clone();
};