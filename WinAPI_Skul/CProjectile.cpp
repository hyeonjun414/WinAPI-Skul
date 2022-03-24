#include "pch.h"
#include "CProjectile.h"
#include "CAnimator.h"
#include "CD2DImage.h"
#include "CCollider.h"
#include "CAnimation.h"

CProjectile::CProjectile(OBJ_TYPE _eType, CObject* _pObj,
	const wstring& _strKey, const wstring& _strPath,
	float _fDuration) :
	CAttack(_eType, _pObj, _fDuration),
	m_bIsGround(false),
	m_bIsHit(false)
{
	SetObjDir(_pObj->GetObjDir());
	SetName(_strKey);
	CreateAnimator();
	m_pAnimator->CreateAnim(_strKey, _strPath, 1.f);
	m_pAnimator->Play(_strKey, true);
	int imgsize = m_pAnimator->GetCurAnim()->GetImg()->GetHeight();
	CreateCollider();
	m_pCollider->SetScale(Vec2(imgsize, imgsize));

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
		m_vPos += m_vVelocity * DT;
		if (m_bIsHit && !m_bIsGround)
		{
			m_vVelocity.y += 1000 * DT;
		}
	}
	GetAnimator()->Update();
}

void CProjectile::Render()
{
	ComponentRender();
}

void CProjectile::OnCollisionEnter(CCollider* _pOther)
{
	if (GetName() == L"BossBomb")
	{
		if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
		{
			SINGLE(CGameManager)->CreateEffect(L"Bomb_Explosion", L"texture\\effect\\ElderEntP2_EnergyCorps_Explosion.png",
				_pOther->GetFinalPos() + Vec2(0, -85), 1.f, 1.f, rand() % 2, 1.f);
			this->SetActive(false);
			DELETEOBJECT(this);
			SINGLE(CSoundManager)->Play(L"BossBombExplosion");
		}
	}
	else if (GetName() == L"Wizard_Fireball")
	{
		if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
		{
			DELETEOBJECT(this);
		}
	}
	else if (GetName() == L"SkulHead")
	{
		if (m_bIsHit && _pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
		{
			m_vVelocity = 0;
			m_bIsGround = true;
		}
		else if (!m_bIsHit && !m_bIgnoreTile)
		{
			if (_pOther->GetFinalPos().x > m_pCollider->GetFinalPos().x)
				m_vPos.x = _pOther->GetFinalPos().x + (-_pOther->GetScale().x - m_pCollider->GetScale().x) / 2 - 30;
			else
				m_vPos.x = _pOther->GetFinalPos().x + (_pOther->GetScale().x + m_pCollider->GetScale().x) / 2 + 30;
			m_vVelocity = 0;
			m_vVelocity.y -= 200;
			m_bIsHit = true;
		}
		if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
		{
			DELETEOBJECT(this);
		}
	}


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
