#include "pch.h"
#include "CUIText.h"

CUIText::CUIText(OBJ_TYPE _eType):
	CUI(_eType),
	m_strText(L""),
	m_fFontSize(14.f),
	m_eFontColor(Color::WHITE)
{
}

CUIText::~CUIText()
{
}

void CUIText::Render()
{
	RENDER->RenderText(
		m_strText,
		GetFinalPos().x,
		GetFinalPos().y,
		GetFinalPos().x + GetScale().x,
		GetFinalPos().y + GetScale().y,
		m_fFontSize,
		2,
		m_eFontColor);

	RenderChild();
}

void CUIText::PositionSet()
{
	SetPos(GetPos() - Vec2(m_strText.size() / 2.f * m_fFontSize, 0));
	SetScale(Vec2(m_strText.size() * m_fFontSize, m_fFontSize));
}
