#include "pch.h"
#include "CEnemyRange.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CStateIdle.h"
#include "CStateAppear.h"
#include "CMeleeAttack.h"
#include "CPlayer.h"
#include "CProjectile.h"
#include "CScene.h"
#include "CTile.h"

CEnemyRange::CEnemyRange(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType):
	CEnemy(_eType, _eEnemyType)
{
	Init();
}

CEnemyRange::~CEnemyRange()
{
}

void CEnemyRange::Init()
{
	switch (GetEnemyType())
	{
	case ENEMY_TYPE::WIZARD:
	{
		CreateAnimator();
		m_pAnimator->CreateAnim(L"Wizard_Idle", L"texture\\enemy\\wizard_idle.png", 0.5f);
		m_pAnimator->CreateAnim(L"Wizard_Teleport", L"texture\\enemy\\wizard_teleport.png", 0.5f);
		m_pAnimator->CreateAnim(L"Wizard_Attack", L"texture\\enemy\\wizard_attack.png", 0.5f);
		m_pAnimator->CreateAnim(L"AppearEnemy", L"texture\\effect\\Enemy_Appearance.png", 1.0f);
		m_pAnimator->CreateAnim(L"DisappearEnemy", L"texture\\effect\\Enemy_Dead.png", 0.5f);



		SetScale(Vec2(160, 160));
		SetName(L"WIZARD");

		CreateCollider();
		// 위치 세부 조정
		m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y / 4));
		m_pCollider->SetScale(Vec2(GetScale() / 2));
		m_pAnimator->SetAllAnimOffset(Vec2(0, 20));


		m_tEnemyInfo.m_iHp = 10;
		m_tEnemyInfo.m_iDamage = 0;
		m_tEnemyInfo.m_vVelocity = Vec2(100.f, 0.f);


		m_fHitDelayTime = 0.1f;
		m_fCurHitTime = 0.f;
		m_bCanHit = true;

		m_fTraceCoolTime = 2.f;
		m_fCurTraceTime = 0.f;
		m_bCanTrace = true;


		m_pState = new CStateAppear();
		m_pState->Enter(this);

		break;
	}
	default:
		break;
	}
}

void CEnemyRange::Update()
{
	CEnemy::Update();
}

void CEnemyRange::Render()
{
	CEnemy::Render();
}

void CEnemyRange::OnCollision(CCollider* _pOther)
{
}

void CEnemyRange::OnCollisionEnter(CCollider* _pOther)
{
	CEnemy::OnCollisionEnter(_pOther);
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER_ATTACK)
	{
		CMeleeAttack* pAttack = (CMeleeAttack*)_pOther->GetObj();

		if (m_bCanHit)
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CPlayer* pPlayer = (CPlayer*)pAttack->GetOwner();
			SINGLE(CSoundManager)->Play(L"Hit");
			SINGLE(CGameManager)->CreateEffect(L"Hit", L"texture\\effect\\hit_normal.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 0.5f, 0.5f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(pPlayer->GetPlayerInfo().m_iDamage), (m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2);
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

			m_tEnemyInfo.m_iHp--;
			m_bCanHit = false;
		}

	}
}

void CEnemyRange::OnCollisionExit(CCollider* _pOther)
{
}

void CEnemyRange::Attack()
{
	CProjectile* pProj = new CProjectile(OBJ_TYPE::PROJECTILE, this,
		L"Wizard_Fireball", L"texture\\effect\\fireball.png", 5.f);
	pProj->SetPos(GetCollider()->GetFinalPos()+Vec2(m_bIsRight? 20.f : -20.f, 0));
	pProj->SetVelocity((PLAYERPOS - pProj->GetPos()).Normalize() * 300.f);
	
	CREATEOBJECT(pProj);

}

void CEnemyRange::Teleport(Vec2 _vTargerPos)
{
	const vector<CObject*>& vecTile = SINGLE(CSceneManager)->GetCurScene()->GetGroupObject(OBJ_TYPE::TILE);
	while (true)
	{
		int randomTileIndex = rand() % vecTile.size();
		// 플레이어와 랜덤 지정한 타일의 거리
		CTile* pTile = (CTile*)vecTile[randomTileIndex];
		
		// 해당 타일이 그라운드 타일이고 거리가 100 이상 400이하 일때 텔레포트를 수행
		if (TILE_TYPE::GROUND == pTile->GetType() ||
			TILE_TYPE::FLOATING == pTile->GetType())
		{
			float dist = (PLAYERPOS - pTile->GetPos()).Length();
			if (200 < dist && dist < 400)
			{
				// 거리 조건 충족시 해당 타일위로 이동을 수행하고 루프 탈출
				SetPos(pTile->GetPos() + Vec2(pTile->GetScale().x/2, 0));
				SetObjDir(GetPos().x < PLAYERPOS.x);
				break;
			}
		}
	}
}
