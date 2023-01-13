#include "ellipse_shape.h"

void EllipseShape::Show(HDC hdc)
{
	Ellipse(hdc, shape.left - (shape.right - shape.left),
		shape.top - (shape.bottom - shape.top), shape.right, shape.bottom);
}

Shape* EllipseShape::Clone()
{
	return new EllipseShape(*this);
}