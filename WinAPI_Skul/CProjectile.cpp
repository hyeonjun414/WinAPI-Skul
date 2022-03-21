#include "pch.h"
#include "CProjectile.h"
#include "CAnimator.h"
#include "CD2DImage.h"
#include "CCollider.h"

CProjectile::CProjectile(OBJ_TYPE _eType, CObject* _pObj,
	const wstring& _strKey, const wstring& _strPath,
	float _fDuration) :
	CAttack(_eType, _pObj, _fDuration),
	m_bIsGround(false),
	m_bIsHit(false)
{
	SetObjDir(_pObj->GetObjDir());

	CreateAnimator();
	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(_strKey, _strPath);
	int imgX = pImg->GetWidth();
	int imgY = pImg->GetHeight();
	int imgCountX = imgX / imgY;
	int imgDiviedSizeX = imgX / imgCountX;
	m_pAnimator->CreateAnimation(_strKey, pImg, Vec2(0, 0), Vec2(imgDiviedSizeX, imgY),
		Vec2(imgDiviedSizeX, 0), (float)(0.5f / imgCountX), imgCountX);
	m_pAnimator->Play(_strKey, true);

	CreateCollider();
	m_pCollider->SetScale(Vec2(imgY*2, imgY*2));

}

CProjectile::~CProjectile()
{
}

void CProjectile::Update()
{
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);

	if (OBJ_TYPE::PROJECTILE == GetObjType())
	{
		m_vPos.x += m_vVelocity.x * DT;
		m_vPos.y -= m_vVelocity.y * DT;
		if (m_bIsHit && !m_bIsGround)
		{
			m_vVelocity.y -= 1000 * DT;
		}
	}
}

void CProjectile::Render()
{
	ComponentRender();
}

void CProjectile::OnCollisionEnter(CCollider* _pOther)
{
	if (m_bIsHit && _pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		m_vVelocity = 0;
		m_bIsGround = true;
	}
	else if (!m_bIsHit)
	{
		if (_pOther->GetFinalPos().x > m_pCollider->GetFinalPos().x)
			m_vPos.x = _pOther->GetFinalPos().x + (-_pOther->GetScale().x - m_pCollider->GetScale().x) / 2 - 30;
		else
			m_vPos.x = _pOther->GetFinalPos().x + (_pOther->GetScale().x + m_pCollider->GetScale().x) / 2 + 30;
		m_vVelocity = 0;
		m_vVelocity.y += 200;
		m_bIsHit = true;
	}
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
	{
		DELETEOBJECT(this);
	}
}
