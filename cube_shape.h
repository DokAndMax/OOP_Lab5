#pragma once
#include "line_shape.h"
#include "rect_shape.h"
class CubeShape : public LineShape, public RectShape
{
public:
	void Show(HDC hdc);
	void ShowPreview(HDC hdc);
	Shape* Clone();
};