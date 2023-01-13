#pragma once
#include "shape.h"

class PointShape : public virtual Shape
{
public:
	void Show(HDC hdc);
	void ShowPreview(HDC hdc);
	Shape* Clone();
};