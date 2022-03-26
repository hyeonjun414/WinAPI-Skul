#include "pch.h"
#include "CEnemy.h"
#include "CEnemyBoss.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTile.h"
#include "CUIText.h"

#include "CEnemyStateIdle.h"


CEnemy::CEnemy(OBJ_TYPE _eType):
	CObject(_eType),
	m_eEnemyType(ENEMY_TYPE::ENEMY_BOSS),
	m_tEnemyInfo{}
{
}

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
	if (nullptr != m_pHpBar)
		delete m_pHpBar;
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

	CoolTime();


	if(nullptr != m_pAnimator)
		m_pAnimator->Update();
	if (nullptr != m_pHpBar)
		m_pHpBar->FinalUpdate();
}

void CEnemy::Render()
{
	ComponentRender();
	RenderEnemyInfo();
	if (nullptr != m_pHpBar)
		m_pHpBar->Render();

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

void CEnemy::Hit(int _damage)
{
	m_tEnemyInfo.m_iHp = m_tEnemyInfo.m_iHp - _damage < 0 ? 0 : m_tEnemyInfo.m_iHp - _damage;
	if (nullptr != m_pHpBar)
	{
		float ratio = m_tEnemyInfo.m_iHp / (float)m_tEnemyInfo.m_iMaxHp < 0.05f ? 0.f : m_tEnemyInfo.m_iHp / (float)m_tEnemyInfo.m_iMaxHp;
		m_pHpBar->SetFrontScale(m_pHpBar->GetBackScale() * ratio);
	}
}

void CEnemy::Die()
{
	SINGLE(CGameManager)->m_iRemainEnemyCount--;
	SINGLE(CGameManager)->m_pRemainEnemy->SetText(to_wstring(SINGLE(CGameManager)->m_iRemainEnemyCount));
	DELETEOBJECT(this);
}

void CEnemy::RenderEnemyInfo()
{
	if (SINGLE(CCore)->GetDebugMode())
	{
		Vec2 pos = GetRenderPos() + Vec2(GetScale().x / 2, -GetScale().y);
		CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"CameraTex", L"texture\\cameraTex.png");
		RENDER->RenderImage(
			pImg,
			pos.x - 3,
			pos.y,
			pos.x + 160,
			pos.y + 90,
			0.3f);
		RENDER->RenderText(
			L"이름 : " + GetName(),
			pos.x,
			pos.y + 20,
			pos.x + 200,
			pos.y,
			16.f,
			0,
			RGB(255, 255, 255));
		RENDER->RenderText(
			L"상태 : " + m_strCurState,
			pos.x,
			pos.y + 50,
			pos.x + 200,
			pos.y,
			16.f,
			0,
			RGB(255, 255, 255));
		RENDER->RenderText(
			L"위치 : (" + to_wstring((int)GetPos().x) + L", " + to_wstring((int)GetPos().y) + L")",
			pos.x,
			pos.y + 80,
			pos.x + 200,
			pos.y,//+ 20 + 100,
			16.f,
			0,
			RGB(255, 255, 255));

		if(nullptr != m_pAnimator)
			RENDER->RenderText(
				L"현재 애니메이션\n : " + GetAnimator()->GetCurAnim()->GetName(),
				pos.x,
				pos.y + 130,
				pos.x + 200,
				pos.y,//+ 20 + 100,
				16.f,
				0,
				RGB(255, 255, 255));
	}
}

void CEnemy::CoolTime()
{
	// 피격 상태 쿨타임
	if (!m_bCanHit && m_fHitDelayTime != 0.f)
	{
		m_fCurHitTime += DT;
		if (m_fCurHitTime >= m_fHitDelayTime)
		{
			m_bCanHit = true;
			m_fCurHitTime = 0.f;
		}
	}
	// 추적 상태 쿨타임
	if (!m_bCanTrace && m_fTraceCoolTime != 0.f)
	{
		m_fCurTraceTime += DT;
		if (m_fCurTraceTime >= m_fTraceCoolTime)
		{
			m_bCanTrace = true;
			m_fCurTraceTime = 0.f;
		}
	}
}

void CEnemy::CreateHealthBar()
{
	CHealthBar* bar = new CHealthBar;
	bar->m_pEnemy = this;
	m_pHpBar = bar;

}
