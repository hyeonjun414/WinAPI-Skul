#include "pch.h"
#include "CUIButton.h"

CUIButton::CUIButton(OBJ_TYPE _eType):
	CUI(_eType),
	m_pFunc(nullptr),
	m_fFontSize(14.f),
	m_eOnColor(Color::BLACK),
	m_eOffColor(Color::BLACK)
{
}

CUIButton::CUIButton(const CUIButton& _origin):
	CUI(_origin),
	m_pFunc(_origin.m_pFunc),
	m_pParam1(_origin.m_pParam1),
	m_pParam2(_origin.m_pParam2)
{
}

CUIButton::~CUIButton()
{
}

CUIButton* CUIButton::Clone()
{
	return new CUIButton(*this);
}

void CUIButton::Update()
{
	CUI::Update();
}

void CUIButton::FinalUpdate()
{
	CUI::FinalUpdate();
}

void CUIButton::Render()
{
	CUI::Render();

	if (m_strText.size() > 0)
	{
		Color eColor = IsMouseOn() ? m_eOnColor : m_eOffColor;
		CRenderManager::GetInst()->RenderText(
			m_strText,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			m_fFontSize,
			2,
			eColor);
	}

	if (nullptr != m_pImg)
	{
		CRenderManager::GetInst()->RenderImage(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			1.0f
		);
	}
}

void CUIButton::MouseOn()
{
	//if (IsMouseOn())
	//{
	//	m_pTex = SINGLE(CResourceManager)->FindTexture(L"BtnClick")
	//}
	
	// 마우스가 올라갔을때 
	//LOG(L"마우스 올라감")

}

void CUIButton::MouseLbtnDown()
{
	LOG(L"마우스 다운");
	// 마우스가 눌렀을때

}

void CUIButton::MouseLbtnUp()
{
	LOG(L"마우스 업");
	// 마우스가 떼어졌을때
}

void CUIButton::MouseLbtnClick()
{
	LOG(L"마우스 클릭")
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CUIButton::SetImage(CD2DImage* _img)
{
	m_pImg = _img;
}

void CUIButton::SetText(const wstring& _str, float _fontSize)
{
	m_strText = _str;
	m_fFontSize = _fontSize;
}

void CUIButton::PositionSet()
{
	SetPos(GetPos() - Vec2(m_strText.size() / 2.f * m_fFontSize, 0));
	SetScale(Vec2(m_strText.size() * m_fFontSize, m_fFontSize));
}

void CUIButton::SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
{
	m_pFunc = _pFunc;
	m_pParam1 = _param1;
	m_pParam2 = _param2;
}
