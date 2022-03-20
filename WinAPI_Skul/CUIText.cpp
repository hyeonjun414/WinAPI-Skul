#include "pch.h"
#include "CUIText.h"

CUIText::CUIText(OBJ_TYPE _eType):
	CUI(_eType)
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
		RGB(255.f,255.f,255.f));

	RenderChild();
}
