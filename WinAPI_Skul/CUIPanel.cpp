#include "pch.h"
#include "CUIPanel.h"

CUIPanel::CUIPanel(OBJ_TYPE _eType):
	CUI(_eType),
	m_vDragStart{}
{
}

CUIPanel::CUIPanel(const CUIPanel& _origin):
	CUI(_origin),
	m_vDragStart{}
{

}

CUIPanel::~CUIPanel()
{
}

CUIPanel* CUIPanel::Clone()
{
	return new CUIPanel(*this);
}

void CUIPanel::MouseOn()
{
	if (IsLbtnDown()) // ����ִ� ��Ȳ�̸�
	{
		// �̵��� ��ŭ�� ���̸� ������ġ�� ������.
		Vec2 vDiff = SINGLE(CKeyManager)->GetMousePos() - m_vDragStart;
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = SINGLE(CKeyManager)->GetMousePos();
	}
}

void CUIPanel::MouseLbtnDown()
{
	m_vDragStart = SINGLE(CKeyManager)->GetMousePos();
}

void CUIPanel::MouseLbtnUp()
{
}
