#include "pch.h"
#include "CEnemy.h"
#include "CEnemyBoss.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CTile.h"

#include "CStateIdle.h"


CEnemy::CEnemy(OBJ_TYPE _eType, ENEMY_TYPE _eMonsterType):
	CObject(_eType),
	m_eEnemyType(_eMonsterType),
	m_tEnemyInfo{}
{
	m_bIsGround = false;
	SINGLE(CGameManager)->m_iRemainEnemyCount++;
}

CEnemy::~CEnemy()
{
	delete m_pState;
}

void CEnemy::Init()
{
	//switch (GetObjGroup())
	//{
	//case OBJ_TYPE::ENEMY_MELEE:
	//	CEnemyMelee* enemy =  new CEnemyMelee(GetObjGroup(), );
	//	CREATEOBJECT(enemy);
	//	break;
	//case OBJ_TYPE::ENEMY_RANGE:
	//	CEnemyRange* enemy = new CEnemyRange();
	//	break;
	//case OBJ_TYPE::ENEMY_BOSS:
	//	CEnemyBoss* enemy = new CEnemyBoss();
	//	break;
	//}
}

void CEnemy::Update()
{
	CState* pState = m_pState->HandleInput(this);
	if (nullptr != pState)
	{
		m_pState->Exit(this);
		delete m_pState;
		m_pState = pState;
		m_pState->Enter(this);
	}

	m_pState->Update(this);

	if(nullptr != m_pAnimator)
		m_pAnimator->Update();
}

void CEnemy::Render()
{
	ComponentRender();
}
void CEnemy::OnCollision(CCollider* _pOther)
{
	//m_pState->OnCollision(this, _pOther);

	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		CTile* pTile = (CTile*)_pOther->GetObj();
		if (pTile->GetType() == TILE_TYPE::FLOATING) return;
		Vec2 pos1 = m_pCollider->GetFinalPos();
		Vec2 pos2 = _pOther->GetFinalPos();
		Vec2 size1 = m_pCollider->GetScale();
		Vec2 size2 = _pOther->GetScale();
		if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
		{
			if (pos1.x <= pos2.x - size2.x / 2)
			{
				m_vPos.x = pos2.x + (-size1.x - size2.x) / 2;//Player->m_vVelocity.x* DT;
			}
			else if (pos1.x >= pos2.x + size2.x / 2)
			{
				m_vPos.x = pos2.x + (size1.x + size2.x) / 2;//Player->m_vVelocity.x* DT;

			}
		}
	}
}

void CEnemy::OnCollisionEnter(CCollider* _pOther)
{
	//m_pState->OnCollisionEnter(this, _pOther);
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		Vec2 vLeftPos = m_pCollider->GetFinalPos();
		Vec2 vLeftScale = m_pCollider->GetScale();
		Vec2 vRightPos = _pOther->GetFinalPos();
		Vec2 vRightScale = _pOther->GetScale();
		m_iCollCount++;
		if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x - 10) / 2.f)
		{

			if (m_iCollCount > 0 &&
				vLeftPos.y <= vRightPos.y - vRightScale.x / 2)
			{
				m_bIsGround = true;
				m_tEnemyInfo.m_vVelocity.y = 0;
				m_vPos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
			}
		}


	}
}

void CEnemy::OnCollisionExit(CCollider* _pOther)
{
	//m_pState->OnCollisionExit(this, _pOther);

	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		m_iCollCount--;
		if (m_iCollCount <= 0)
		{
			m_iCollCount = 0;
			m_bIsGround = false;
		}

	}
}
