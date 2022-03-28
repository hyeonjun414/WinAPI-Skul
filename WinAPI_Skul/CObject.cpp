#include "pch.h"
#include "CObject.h"
#include "CCollider.h"
#include "CAnimator.h"

CObject::CObject():
	m_bIsDead(true),
	m_pCollider(nullptr),
	m_pAnimator(nullptr)
{
	m_eType = OBJ_TYPE::DEFAULT;
}

CObject::CObject(OBJ_TYPE _eType) :
	m_bIsDead(true),
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_bIsActive(true)
{
	m_eType = _eType;
}

CObject::CObject(const CObject& _origin) :
	m_strName(_origin.m_strName),
	m_eType(_origin.m_eType),
	m_bIsDead(true),
	m_vPos(_origin.m_vPos),
	m_vScale(_origin.m_vScale),
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
CObject::~CObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CObject::Init()
{
}

void CObject::Update()
{
	if (nullptr != m_pAnimator)
		m_pAnimator->Update();
}

void CObject::Render()
{
	ComponentRender();
}

void CObject::FinalUpdate()
{
	m_vRenderPos = SINGLE(CCameraManager)->GetRenderPos(m_vPos);
	if (nullptr != m_pCollider)
		m_pCollider->FinalUpdate();
}

void CObject::ComponentRender()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(m_bIsRight);
		RenderObjCenter();
	}

	if (nullptr != m_pCollider && SINGLE(CCore)->GetDebugMode())
	{
		m_pCollider->Render();
	}
		
	
	
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::RenderObjCenter()
{
	if (SINGLE(CCore)->GetDebugMode())
	{
		RENDER->RenderFillEllipse(
			GetRenderPos().x - 2,
			GetRenderPos().y - 2,
			4,
			4,
			RGB(255,0,255));
		
	}
}
