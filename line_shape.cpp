#include "line_shape.h"

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, shape.left, shape.top, NULL);
	LineTo(hdc, shape.right, shape.bottom);
}

Shape* LineShape::Clone()
{
	return new LineShape(*this);
}