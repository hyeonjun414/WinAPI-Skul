#include "pch.h"
#include "CMeleeAttack.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CTextObj.h"

CMeleeAttack::CMeleeAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration):
	CAttack(_eType, _pObj, _fDuration)
{
}

CMeleeAttack::~CMeleeAttack()
{
}

void CMeleeAttack::Update()
{
	SetPos(m_pOwner->GetPos());
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);
}

void CMeleeAttack::Render()
{
	ComponentRender();
}

void CMeleeAttack::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::ENEMY)
	{
		CEnemy* pEnemy = (CEnemy*)_pOther->GetObj();
		if (pEnemy->CanHit())
		{
			CPlayer* pPlayer = (CPlayer*)GetOwner();
		}

	}
	if (GetObjType() == OBJ_TYPE::BOSS_ATTACK &&
		_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		SINGLE(CGameManager)->CreateEffect(L"BigStemp", L"texture\\effect\\BigStomp_Attack_Smoke.png",
			(m_pCollider->GetFinalPos() + _pOther->GetFinalPos())/2 + Vec2(0,-100),
			2.f, 2.f, true);
	}
}

void CMeleeAttack::CreateAttackArea(CObject* _pObj, Vec2 _vPos, Vec2 _vScale)
{
	CreateCollider();
	SetPos(_pObj->GetPos());
	m_pCollider->SetOffsetPos(Vec2(0, -_pObj->GetScale().y / 4));
	if (_pObj->GetObjDir())
	{
		m_pCollider->SetOffsetPos(Vec2(_vPos.x, -_pObj->GetScale().y / 4));
	}
	else
	{
		m_pCollider->SetOffsetPos(Vec2(-_vPos.x, -_pObj->GetScale().y / 4));
	}

	m_pCollider->SetScale(_vScale);
}
