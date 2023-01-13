#include "lineoo_shape.h"

#define ELLIPSE_RADIUS 15

void LineOOShape::Show(HDC hdc)
{
	RECT temp = shape;

	LineShape::Show(hdc);
	Set(temp.left, temp.top, temp.left + ELLIPSE_RADIUS, temp.top + ELLIPSE_RADIUS);
	EllipseShape::Show(hdc);
	Set(temp.right, temp.bottom, temp.right + ELLIPSE_RADIUS, temp.bottom + ELLIPSE_RADIUS);
	EllipseShape::Show(hdc);

	Set(temp.left, temp.top, temp.right, temp.bottom);
}

Shape* LineOOShape::Clone()
{
	return new LineOOShape(*this);
}