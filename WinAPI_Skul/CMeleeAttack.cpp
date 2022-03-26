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
	if (nullptr != m_pTraceObj)
	{
		SetPos(m_pTraceObj->GetPos());
	}
	else
	{
		SetPos(m_pOwner->GetPos());
	}
	
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
	else if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
	{

	}
	else if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		if (GetObjType() == OBJ_TYPE::MELEE_ATTACK)
		{ 
			if (GetName() == L"Slam")
			{
				SINGLE(CGameManager)->CreateVfx(L"BigStemp", L"texture\\effect\\BigStomp_Attack_Smoke.png",
					Vec2((m_pCollider->GetFinalPos().x + _pOther->GetFinalPos().x) / 2 + rand() % 100 - 50,
						_pOther->GetFinalPos().y - 160 + rand() % 30 - 15),
					2.f, 2.f, rand() % 2);
				SINGLE(CCameraManager)->CameraShaking(2500, 1.f);
				SINGLE(CSoundManager)->Play(L"BossSlam");
			}
			else if (GetName() == L"Sweep")
			{
				SINGLE(CGameManager)->CreateVfx(L"BigStemp", L"texture\\effect\\BigStomp_Attack_Smoke.png",
					Vec2((m_pCollider->GetFinalPos().x + _pOther->GetFinalPos().x) / 2 + rand() % 100 - 50,
						_pOther->GetFinalPos().y - 160 + rand() % 30 - 15),
					0.5f, 0.5f, rand() % 2);
			}
		}
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
