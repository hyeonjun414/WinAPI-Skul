#include "pch.h"
#include "CCollider.h"
#include "CObject.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider():
	m_pOwner(nullptr),
	m_uiID(g_iNextID++),
	m_uiColCount(0)
{
}

CCollider::CCollider(const CCollider& _origin) :
	m_pOwner(nullptr),
	m_vOffsetPos(_origin.m_vOffsetPos),
	m_vScale(_origin.m_vScale),
	m_uiID(g_iNextID++),
	m_uiColCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// �浹ü�� Object�� ��ġ�� ���󰡵��� �����.
	// FinalPos�� ���� �浹�� �Ͼ�� ��ǥ�̱� ������ RenderPos�� �����ϸ� �ȵȴ�.
	// FinalPos�� �������� RenderPos�� ��������
	m_vFinalPos = m_pOwner->GetPos() + m_vOffsetPos;
	m_vRenderPos = SINGLE(CCameraManager)->GetRenderPos(m_vFinalPos);
	assert(m_uiColCount >= 0);
}

void CCollider::Render()
{
	if (m_uiColCount > 0)
	{
		RENDER->RenderRectangle(
			m_vRenderPos.x - m_vScale.x / 2,
			m_vRenderPos.y - m_vScale.y / 2,
			m_vRenderPos.x + m_vScale.x / 2,
			m_vRenderPos.y + m_vScale.y / 2,
			RGB(255, 0, 0));
	}
	else
	{
		RENDER->RenderRectangle(
			m_vRenderPos.x - m_vScale.x / 2,
			m_vRenderPos.y - m_vScale.y / 2,
			m_vRenderPos.x + m_vScale.x / 2,
			m_vRenderPos.y + m_vScale.y / 2,
			RGB(0, 255, 0));
	}


}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_uiColCount;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_uiColCount;
	m_pOwner->OnCollisionExit(_pOther);
}
