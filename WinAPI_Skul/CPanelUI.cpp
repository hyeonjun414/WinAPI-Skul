#include "pch.h"
#include "CPanelUI.h"

CPanelUI::CPanelUI(OBJ_TYPE _eType):
	CUI(_eType),
	m_vDragStart{}
{
}

CPanelUI::CPanelUI(const CPanelUI& _origin):
	CUI(_origin),
	m_vDragStart{}
{

}

CPanelUI::~CPanelUI()
{
}

CPanelUI* CPanelUI::Clone()
{
	return new CPanelUI(*this);
}

void CPanelUI::MouseOn()
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

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = SINGLE(CKeyManager)->GetMousePos();
}

void CPanelUI::MouseLbtnUp()
{
}
