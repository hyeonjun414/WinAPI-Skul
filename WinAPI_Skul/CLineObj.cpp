#include "pch.h"
#include "CLineObj.h"

CLineObj::CLineObj(CObject* _pStart, CObject* _pEnd, Vec2 _offsetStart, Vec2 _offsetEnd, float _size):
	CObject(OBJ_TYPE::LINE),
	m_pStart(_pStart),
	m_pEnd(_pEnd),
	m_fSize(_size),
	m_vOffsetStart(_offsetStart),
	m_vOffsetEnd(_offsetEnd)
{
}

CLineObj::~CLineObj()
{
}

void CLineObj::Render()
{
	RENDER->RenderLine(
		m_pStart->GetRenderPos() + m_vOffsetStart,
		m_pEnd->GetRenderPos() + m_vOffsetEnd,
		RGB(28, 12, 32),
		m_fSize);
}
