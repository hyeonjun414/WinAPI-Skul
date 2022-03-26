#include "pch.h"
#include "CProjectile.h"
#include "CAnimator.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CAnimation.h"

CProjectile::CProjectile(OBJ_TYPE _eType, CObject* _pObj, float _fDuration) :
	CAttack(_eType, _pObj, _fDuration),
	m_bIsGround(false),
	m_bIsHit(false)
{

}

CProjectile::~CProjectile()
{
}

void CProjectile::Update()
{

}

void CProjectile::Render()
{
	ComponentRender();
}

void CProjectile::OnCollisionEnter(CCollider* _pOther)
{
	
}

void CProjectile::Move(Vec2 _vVelocity, float _fDelay)
{
}

void CProjectile::Stop(float _fDelay)
{
}

void CProjectile::Trace(CObject* _pObj, Vec2 _vVelocity, float _fTraceTime)
{
}
