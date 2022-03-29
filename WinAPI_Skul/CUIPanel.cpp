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

void CUIPanel::Render()
{
	Vec2 vPos = m_vFinalPos;
	Vec2 vScale = m_vScale;

	if (m_bCameraAffected)
	{
		vPos = SINGLE(CCameraManager)->GetRenderPos(vPos);
	}


	if (m_bLbtnDown)
	{
		RENDER->RenderFillRectangle(
			vPos.x,
			vPos.y,
			vPos.x + vScale.x,
			vPos.y + vScale.y,
			RGB(255, 255, 255)
		);
		RENDER->RenderRectangle(
			vPos.x,
			vPos.y,
			vPos.x + vScale.x,
			vPos.y + vScale.y,
			RGB(0, 255, 0));
	}
	else
	{
		RENDER->RenderFillRectangle(
			vPos.x,
			vPos.y,
			vPos.x + vScale.x,
			vPos.y + vScale.y,
			RGB(255, 255, 255)
		);
		RENDER->RenderRectangle(
			vPos.x,
			vPos.y,
			vPos.x + vScale.x,
			vPos.y + vScale.y,
			RGB(0, 0, 0));
	}


	RenderChild();

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
