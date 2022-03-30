#include "pch.h"
#include "CEnemyMelee.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CEnemyStateAppear.h"
#include "CMeleeAttack.h"
#include "CPlayer.h"

CEnemyMelee::CEnemyMelee(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType):
	CEnemy(_eType, _eEnemyType)

{
	Init();
}

CEnemyMelee::~CEnemyMelee()
{
}

void CEnemyMelee::Init()
{
	switch (GetEnemyType())
	{
	case ENEMY_TYPE::BIG_KNIGHT:
	{
		CreateAnimator();
		m_pAnimator->CreateAnim(L"BigKnight_Idle", L"texture\\enemy\\big_knight_idle.png", 0.8f);
		m_pAnimator->CreateAnim(L"BigKnight_Move", L"texture\\enemy\\big_knight_move.png", 0.8f);
		m_pAnimator->CreateAnim(L"BigKnight_AttacKA", L"texture\\enemy\\big_knight_attacka.png", 0.6f);
		m_pAnimator->CreateAnim(L"BigKnight_AttacKB", L"texture\\enemy\\big_knight_attackb.png", 4.0f);
		m_pAnimator->CreateAnim(L"BigKnight_Die", L"texture\\enemy\\big_knight_die.png", 0.5f);
		m_pAnimator->CreateAnim(L"AppearEnemy", L"texture\\effect\\Enemy_Appearance.png", 1.0f);
		m_pAnimator->CreateAnim(L"DisappearEnemy", L"texture\\effect\\Enemy_Dead.png", 0.5f);

		SetScale(Vec2(160, 160));
		SetName(L"Big_Knight");
		CreateCollider();
		
		// 위치 세부 조정
		m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y / 4));
		m_pCollider->SetScale(Vec2(GetScale() / 2));
		m_pAnimator->SetAllAnimOffset(Vec2(0, 0));


		m_tEnemyInfo.m_iHp = 1000;
		m_tEnemyInfo.m_iMaxHp = 1000;
		m_tEnemyInfo.m_iDamage = 1;
		m_tEnemyInfo.m_vVelocity = Vec2(100.f, 0.f);

		
		m_bCanAttack = true;
		m_fAttackDeleyTime = 1.f;
		m_fCurAttackTime = 0.f;

		m_fHitDelayTime = 0.1f;
		m_fCurHitTime = 0.f;
		m_bCanHit = true;
		
		CreateHealthBar();

		m_pState = new CEnemyStateAppear();
		m_pState->Enter(this);

		break;
	}
	default:
		break;
	}
}

void CEnemyMelee::Update()
{
	CEnemy::Update();
}

void CEnemyMelee::Render()
{
	CEnemy::Render();
}

void CEnemyMelee::OnCollision(CCollider* _pOther)
{
	CEnemy::OnCollision(_pOther);
}

void CEnemyMelee::OnCollisionEnter(CCollider* _pOther)
{
	CEnemy::OnCollisionEnter(_pOther);
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER_ATTACK)
	{
		CMeleeAttack* pAttack = (CMeleeAttack*)_pOther->GetObj();

		if (m_bCanHit)
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CPlayer* pPlayer = (CPlayer*)pAttack->GetOwner();
			int damage = SINGLE(CGameManager)->RandomInt(pPlayer->GetPlayerInfo().m_iDamage, 0.2f);
			SINGLE(CSoundManager)->Play(L"Hit");
			SINGLE(CGameManager)->CreateVfx(L"Hit", L"texture\\effect\\hit_normal.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 0.5f, 0.5f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(damage), (m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2);
			if (pAttack->GetOwner()->GetPos().x < m_pCollider->GetFinalPos().x)
			{
				//SetPos(GetPos() + Vec2(10, 0));
				SetObjDir(false);
			}
			else
			{
				//SetPos(GetPos() + Vec2(-10, 0));
				SetObjDir(true);
			}

			Hit(damage);
			m_bCanHit = false;
		}

	}
}

void CEnemyMelee::OnCollisionExit(CCollider* _pOther)
{
	CEnemy::OnCollisionExit(_pOther);
}

void CEnemyMelee::Attack()
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::MELEE_ATTACK, this, 0.5f);
	pAttack->CreateAttackArea(this, Vec2(60, 50), Vec2(100, 80));
	CREATEOBJECT(pAttack);
}
