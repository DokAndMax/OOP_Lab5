#include "rect_shape.h"

void RectShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 128, 0));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void RectShape::ShowPreview(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
}

Shape* RectShape::Clone()
{
	return new RectShape(*this);
}