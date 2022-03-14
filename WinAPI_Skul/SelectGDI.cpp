#include "pch.h"

SelectGDI::SelectGDI(HDC _hDC, PEN_TYPE _penType, BRUSH_TYPE _brushType) :
	m_hDC(_hDC),
	m_hDefaultBrush(nullptr),
	m_hDefaultPen(nullptr)
{
	HPEN hPen = SINGLE(CCore)->GetPEN(_penType);
	m_hDefaultPen = (HPEN)SelectObject(_hDC, hPen);

	HBRUSH hBrush = SINGLE(CCore)->GetBrush(_brushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_hDC, hBrush);
}
SelectGDI::SelectGDI(HDC _hDC, PEN_TYPE _penType):
	m_hDC(_hDC),
	m_hDefaultBrush(nullptr),
	m_hDefaultPen(nullptr)
{
	HPEN hPen = SINGLE(CCore)->GetPEN(_penType);
	m_hDefaultPen = (HPEN)SelectObject(_hDC, hPen);

}
SelectGDI::SelectGDI(HDC _hDC, BRUSH_TYPE _brushType):
	m_hDC(_hDC),
	m_hDefaultBrush(nullptr),
	m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = SINGLE(CCore)->GetBrush(_brushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_hDC, hBrush);
}
SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}
