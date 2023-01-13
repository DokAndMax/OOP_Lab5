#pragma once
#include "line_shape.h"
#include "ellipse_shape.h"
class LineOOShape : public LineShape, public EllipseShape
{
public:
	void Show(HDC hdc);
	Shape* Clone();
};