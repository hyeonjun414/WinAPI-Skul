#include "pch.h"
#include "CCollider.h"
#include "CGameObject.h"

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

void CCollider::Render(HDC _hDC)
{
	SelectGDI GDI(_hDC, m_uiColCount > 0? PEN_TYPE::RED : PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW);


	Rectangle(_hDC,
		(int)(m_vRenderPos.x - m_vScale.x / 2),
		(int)(m_vRenderPos.y - m_vScale.y / 2),
		(int)(m_vRenderPos.x + m_vScale.x / 2),
		(int)(m_vRenderPos.y + m_vScale.y / 2));
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
