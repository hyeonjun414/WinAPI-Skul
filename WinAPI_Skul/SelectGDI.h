#pragma once
class SelectGDI
{
private:
	HDC	m_hDC;
	HPEN m_hDefaultPen;
	HBRUSH m_hDefaultBrush;

public:
	SelectGDI(HDC _hDC, PEN_TYPE _penType, BRUSH_TYPE _brushType);
	SelectGDI(HDC _hDC, PEN_TYPE _penType);
	SelectGDI(HDC _hDC, BRUSH_TYPE _brushType);
	~SelectGDI();
};