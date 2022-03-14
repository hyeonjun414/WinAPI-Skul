#include "pch.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI(OBJ_TYPE _eType):
	CUI(_eType),
	m_pFunc(nullptr)
{
}

CButtonUI::CButtonUI(const CButtonUI& _origin):
	CUI(_origin),
	m_pFunc(_origin.m_pFunc),
	m_pParam1(_origin.m_pParam1),
	m_pParam2(_origin.m_pParam2)
{
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::MouseOn()
{
	//if (IsMouseOn())
	//{
	//	m_pTex = SINGLE(CResourceManager)->FindTexture(L"BtnClick")
	//}
	
	// 마우스가 올라갔을때 
	LOG(L"마우스 올라감")
}

void CButtonUI::MouseLbtnDown()
{
	LOG(L"마우스 다운");
	// 마우스가 눌렀을때
}

void CButtonUI::MouseLbtnUp()
{
	LOG(L"마우스 업");
	// 마우스가 떼어졌을때
}

void CButtonUI::MouseLbtnClick()
{
	LOG(L"마우스 클릭")
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CButtonUI::SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
{
	m_pFunc = _pFunc;
	m_pParam1 = _param1;
	m_pParam2 = _param2;
}
