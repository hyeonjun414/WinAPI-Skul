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
	
	// ���콺�� �ö����� 
	LOG(L"���콺 �ö�")
}

void CButtonUI::MouseLbtnDown()
{
	LOG(L"���콺 �ٿ�");
	// ���콺�� ��������
}

void CButtonUI::MouseLbtnUp()
{
	LOG(L"���콺 ��");
	// ���콺�� ����������
}

void CButtonUI::MouseLbtnClick()
{
	LOG(L"���콺 Ŭ��")
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
