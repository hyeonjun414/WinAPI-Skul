#include "pch.h"
#include "CUIButton.h"

CUIButton::CUIButton(OBJ_TYPE _eType):
	CUI(_eType),
	m_pFunc(nullptr)
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

void CUIButton::Render()
{
	CUI::Render();

	if (m_strText.size() > 0)
	{
		CRenderManager::GetInst()->RenderText(
			m_strText,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y
		);
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
	
	// ���콺�� �ö����� 
	LOG(L"���콺 �ö�")
}

void CUIButton::MouseLbtnDown()
{
	LOG(L"���콺 �ٿ�");
	// ���콺�� ��������
}

void CUIButton::MouseLbtnUp()
{
	LOG(L"���콺 ��");
	// ���콺�� ����������
}

void CUIButton::MouseLbtnClick()
{
	LOG(L"���콺 Ŭ��")
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CUIButton::SetImage(CD2DImage* _img)
{
	m_pImg = _img;
}

void CUIButton::SetText(const wstring& _str)
{
	m_strText = _str;
}

void CUIButton::SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
{
	m_pFunc = _pFunc;
	m_pParam1 = _param1;
	m_pParam2 = _param2;
}
