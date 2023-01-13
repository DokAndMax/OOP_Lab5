#include "cube_shape.h"

#define PERCENT 0.25

void CubeShape::Show(HDC hdc)
{
	RECT temp = shape;

	if (temp.right - temp.left < 0)
		Set(temp.right, shape.top, temp.left, shape.bottom);

	if (temp.bottom - temp.top < 0)
		Set(shape.left, temp.bottom, shape.right, temp.top);

	POINT delta{ (LONG)((shape.right - shape.left) * PERCENT),
			(LONG)((shape.bottom - shape.top) * PERCENT) };

	RECT rect1{ shape.left + delta.x, shape.top,
	 shape.right, shape.bottom - delta.y };
	RECT rect2{ shape.left, shape.top + delta.y,
	shape.right - delta.x, shape.bottom };

	Set(rect2.left, rect2.top, rect2.right, rect2.bottom);
	RectShape::Show(hdc);
	Set(rect1.left, rect1.top, rect2.left, rect2.top);
	LineShape::Show(hdc);
	Set(rect1.right, rect1.top, rect2.right, rect2.top);
	LineShape::Show(hdc);
	Set(rect1.right, rect1.bottom, rect2.right, rect2.bottom);
	LineShape::Show(hdc);
	Set(rect1.left, rect1.top, rect1.right, rect1.top);
	LineShape::Show(hdc);
	Set(rect1.right, rect1.top, rect1.right, rect1.bottom);
	LineShape::Show(hdc);

	Set(temp.left, temp.top, temp.right, temp.bottom);
}

void CubeShape::ShowPreview(HDC hdc)
{
	Show(hdc);
}

Shape* CubeShape::Clone()
{
	return new CubeShape(*this);
}