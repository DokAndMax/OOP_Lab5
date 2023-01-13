#include "point_shape.h"

#define PIXEL_SIZE 4

void PointShape::Show(HDC hdc)
{
	RECT rect = shape;
	rect.left -= (PIXEL_SIZE / 2);
	rect.top -= (PIXEL_SIZE / 2);
	rect.right = shape.left + (PIXEL_SIZE / 2);
	rect.bottom = shape.top + (PIXEL_SIZE / 2);

	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));

	FillRect(hdc, &rect, brush);

	DeleteObject(brush);
}

void PointShape::ShowPreview(HDC hdc)
{
}

Shape* PointShape::Clone()
{
	return new PointShape(*this);
}