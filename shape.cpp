#include "shape.h"

Shape::~Shape()
{
}

//---���������� ������ Set---
void Shape::Set(long x1, long y1, long x2, long y2)
{
	shape.left = x1;
	shape.top = y1;
	shape.right = x2;
	shape.bottom = y2;
}

//---���������� ������ Get---
RECT Shape::Get()
{
	return shape;
}

void Shape::ShowPreview(HDC hdc)
{
	Show(hdc);
}