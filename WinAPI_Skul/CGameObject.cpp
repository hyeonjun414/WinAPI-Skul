#include "pch.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CAnimator.h"

CGameObject::CGameObject():
	m_bIsActive(true),
	m_bIsGravity(false),
	m_pTex(nullptr),
	m_pCollider(nullptr),
	m_pAnimator(nullptr)
{
	m_eType = OBJ_TYPE::DEFAULT;
}

CGameObject::CGameObject(OBJ_TYPE _eType) :
	m_bIsActive(true),
	m_bIsGravity(false),
	m_pTex(nullptr),
	m_pCollider(nullptr),
	m_pAnimator(nullptr)
{
	m_eType = _eType;
}

CGameObject::CGameObject(const CGameObject& _origin) :
	m_strName(_origin.m_strName),
	m_eType(_origin.m_eType),
	m_bIsActive(true),
	m_bIsGravity(_origin.m_bIsGravity),
	m_vPos(_origin.m_vPos),
	m_vScale(_origin.m_vScale),
	m_pTex(_origin.m_pTex),
	m_pCollider(nullptr),
	m_pAnimator(nullptr)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}
CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CGameObject::FinalUpdate()
{
	m_vRenderPos = SINGLE(CCameraManager)->GetRenderPos(m_vPos);
	if (nullptr != m_pCollider)
		m_pCollider->FinalUpdate();
}

void CGameObject::ComponentRender(HDC _hDC)
{
	if (nullptr != m_pCollider && SINGLE(CCore)->GetDebugMode())
		m_pCollider->Render(_hDC);

	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_hDC);
}



void CGameObject::TextureRender(HDC _hDC)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	TransparentBlt(_hDC,
		(int)(m_vRenderPos.x - (iWidth / 2)),
		(int)(m_vRenderPos.y - (iHeight / 2) - m_vScale.y/2),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 0, 255));
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}
