#include "pch.h"
#include "CEnemyMelee.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CD2DImage.h"

#include "CFuncObj.h"
#include "CStateIdle.h"
#include "CStateAppear.h"

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
		CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"BigKnight_Idle", L"texture\\enemy\\big_knight_idle.png");
		m_pAnimator->CreateAnimation(L"BigKnight_Idle", pImg, Vec2(0, 0), Vec2(160, 160), Vec2(160, 0), 0.2f, 4);
		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"BigKnight_Move", L"texture\\enemy\\big_knight_move.png");
		m_pAnimator->CreateAnimation(L"BigKnight_Move", pImg, Vec2(0, 0), Vec2(160, 160), Vec2(160, 0), 0.1f, 8);
		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"BigKnight_AttacKA", L"texture\\enemy\\big_knight_attacka.png");
		m_pAnimator->CreateAnimation(L"BigKnight_AttacKA", pImg, Vec2(0, 0), Vec2(160, 160), Vec2(160, 0), 0.1f, 6);
		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"BigKnight_AttacKB", L"texture\\enemy\\big_knight_attackb.png");
		m_pAnimator->CreateAnimation(L"BigKnight_AttacKB", pImg, Vec2(0, 0), Vec2(160, 160), Vec2(160, 0), 2.f, 2);
		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"BigKnight_Die", L"texture\\enemy\\big_knight_die.png");
		m_pAnimator->CreateAnimation(L"BigKnight_Die", pImg, Vec2(0, 0), Vec2(160, 160), Vec2(160, 0), 2.f, 1);
		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"AppearEnemy", L"texture\\effect\\Enemy_Appearance.png");
		m_pAnimator->CreateAnimation(L"AppearEnemy", pImg, Vec2(0, 0), Vec2(128, 128), Vec2(128, 0), 1.0f/11.f, 11);

		pImg = SINGLE(CResourceManager)->LoadD2DImage(L"DisappearEnemy", L"texture\\effect\\Enemy_Dead.png");
		m_pAnimator->CreateAnimation(L"DisappearEnemy", pImg, Vec2(0, 0), Vec2(128, 128), Vec2(128, 0), 0.5f/6.f, 6);

		CreateCollider();
		m_pCollider->SetScale(Vec2(100, 120));
		m_pCollider->SetOffsetPos(Vec2(0, 30));
		
		m_iHp = 10;
		m_iDamage = 0;
		m_vVelocity = Vec2(100.f, 0.f);

		m_pState = new CStateAppear();
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
}

void CEnemyMelee::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER_ATTACK)
	{
		CFuncObj* pAttack = (CFuncObj*)_pOther->GetObj();

		if (pAttack->GetOwner()->GetPos().x < m_pCollider->GetFinalPos().x)
		{
			SetPos(GetPos() + Vec2(10, 0));
			SetObjDir(false);
		}
		else
		{
			SetPos(GetPos() + Vec2(-10, 0));
			SetObjDir(true);
		}

		m_iHp--;
	}
}

void CEnemyMelee::OnCollisionExit(CCollider* _pOther)
{
}