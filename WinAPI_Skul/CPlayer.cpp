#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CStateIdle.h"
#include "CFuncAttack.h"
#include "CTile.h"

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CObject(_objGroup)
{
	m_bIsGround = false;
	m_bIsRight = true;
	m_iCollCount = 0;
	m_vVelocity = Vec2(300, 0);

	m_bCanDoubleJump = false;
	m_bCanSecondDash = true;
	m_bCanDash = true;
	m_bCanJumpAttack = true;
	m_bCanSkill = true;

	m_fSecondDashCoolTime = 2.f;
	m_fSecondDashCurTime = 0.f;

	m_fDashCoolTime = 1.f;
	m_fDashCurTime = 0.f;

	m_fSkillCoolTime = 5.0f;
	m_fSkillCurTime = 0;

	SetScale(Vec2(96, 96));

	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y/4));
	m_pCollider->SetScale(Vec2(GetScale()/2));

	
	CreateAnimator();
	CD2DImage* pImg;
	// 애니메이터 만들기
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Idle", L"texture\\player\\idle_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Idle", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.15f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Move", L"texture\\player\\move_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Move", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 8);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Jump", L"texture\\player\\jump_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Jump", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Fall", L"texture\\player\\fall_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Fall", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.5f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_FallRepeat", L"texture\\player\\fallrepeat_skul.png");
	GetAnimator()->CreateAnimation(L"Player_FallRepeat", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.2f, 3);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackA", L"texture\\player\\attackA_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackA", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 5);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackB", L"texture\\player\\attackB_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackB", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.125f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_SkillA", L"texture\\player\\skillA_skul.png");
	GetAnimator()->CreateAnimation(L"Player_SkillA", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.125f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_SkillB", L"texture\\player\\skillB_skul.png");
	GetAnimator()->CreateAnimation(L"Player_SkillB", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 1.f/9.f, 9);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Dash", L"texture\\player\\dash_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Dash", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 1.0f, 1);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_JumpAttack", L"texture\\player\\jumpattack_skul.png");
	GetAnimator()->CreateAnimation(L"Player_JumpAttack", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.125f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Idle_Headless", L"texture\\player\\idle_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Idle_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.15f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Move_Headless", L"texture\\player\\move_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Move_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 8);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Jump_Headless", L"texture\\player\\jump_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Jump_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Fall_Headless", L"texture\\player\\fall_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Fall_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.5f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_FallRepeat_Headless", L"texture\\player\\fallrepeat_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_FallRepeat_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.2f, 3);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackA_Headless", L"texture\\player\\attackA_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackA_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.1f, 5);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackB_Headless", L"texture\\player\\attackB_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackB_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.125f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Dash_Headless", L"texture\\player\\dash_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Dash_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 1.0f, 1);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_JumpAttack_Headless", L"texture\\player\\jumpattack_headless_skul.png");
	GetAnimator()->CreateAnimation(L"Player_JumpAttack_Headless", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),Vec2(96, 0.f), 0.125f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_SkillRebone", L"texture\\player\\skill_rebone_skul.png");
	GetAnimator()->CreateAnimation(L"Player_SkillRebone", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f), Vec2(96, 0.f), 0.5f/8.f, 8);


	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset(Vec2(0,30));

	m_pState = new CStateIdle();
	m_pState->Enter(this);

	SINGLE(CSoundManager)->AddSound(L"Jump", L"sound\\Default_Jump.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAir", L"sound\\Default_Jump_Air.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackA", L"sound\\Legacy_AttackA.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackB", L"sound\\Legacy_AttackB.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Dash", L"sound\\Default_Dash.wav", false);

	GetPlayerInfo().m_iDamage = 1;

}

CPlayer::~CPlayer()
{
	delete m_pState;

	if (nullptr != SINGLE(CCameraManager)->GetTarget())
	{
		SINGLE(CCameraManager)->SetTarget(nullptr);
	}
}

void CPlayer::Init()
{
}

void CPlayer::Update()
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
	GetAnimator()->Update();
}

void CPlayer::Render()
{
	ComponentRender();
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	//m_pState->OnCollision(this, _pOther);

    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE )
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

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	//m_pState->OnCollisionEnter(this, _pOther);
    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
    {
		Vec2 vLeftPos = m_pCollider->GetFinalPos();
		Vec2 vLeftScale = m_pCollider->GetScale();
		Vec2 vRightPos = _pOther->GetFinalPos();
		Vec2 vRightScale = _pOther->GetScale();
		pPlayer->m_iCollCount++;
		if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x-10) / 2.f)
		{
			
			if (pPlayer->m_iCollCount > 0 && 
				vLeftPos.y <= vRightPos.y - vRightScale.x/2)
			{
				pPlayer->m_bIsGround = true;
				m_bCanJumpAttack = true;
				m_bCanDoubleJump = true;
				m_vVelocity.y = 0;
				m_vPos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
			}
		}
    }
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PROJECTILE &&
		_pOther->GetObj()->GetName() == L"SkulHead")
	{
		DELETEOBJECT(_pOther->GetObj());
		m_bCanSkill = true;
		m_fSkillCurTime = 0.f;

	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	//m_pState->OnCollisionExit(this, _pOther);

    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
    {
		pPlayer->m_iCollCount--;
		if (pPlayer->m_iCollCount <= 0)
		{
			pPlayer->m_iCollCount = 0;
			pPlayer->m_bIsGround = false;
		}

    }
}

void CPlayer::CoolTime()
{
	// 모든 상태에서 계산되어야하는 부분은 이부분에서 처리한다.
	if (!m_bCanSecondDash)
	{
		m_fSecondDashCurTime += DT;
		if (m_fSecondDashCurTime >= m_fSecondDashCoolTime)
		{
			m_bCanSecondDash = true;
			m_fSecondDashCurTime = 0.f;

		}
	}

	if (!m_bCanDash)
	{
		m_fDashCurTime += DT;
		if (m_fDashCurTime >= m_fDashCoolTime)
		{
			m_bCanDash = true;
		}
	}

	if (!m_bCanSkill)
	{
		m_fSkillCurTime += DT;
		if (m_fSkillCurTime >= m_fSkillCoolTime)
		{
			m_bCanSkill = true;

		}
	}
}

void CPlayer::Attack()
{
	
	CFuncAttack* pAttack = new CFuncAttack(OBJ_TYPE::PLAYER_ATTACK, L"Hit_Normal", L"texture\\effect\\hit_normal.png",
		0.5f, 0.5f, 96, m_bIsRight);
	pAttack->SetOwner(this);
	pAttack->CreateAttackArea(this, Vec2(50, 0), Vec2(50, 100));
	CREATEOBJECT(pAttack);

}

void CPlayer::JumpAttack()
{
	CFuncAttack* pAttack = new CFuncAttack(OBJ_TYPE::PLAYER_ATTACK, L"Hit_Normal", L"texture\\effect\\hit_normal.png",
		0.5f, 0.5f, 96, m_bIsRight);
	pAttack->SetOwner(this);
	pAttack->CreateAttackArea(this, Vec2(50, 50), Vec2(50, 70));
	CREATEOBJECT(pAttack);
}

void CPlayer::SkillA()
{
	CFuncAttack* pAttack = new CFuncAttack(OBJ_TYPE::PROJECTILE, L"Skul_Head", L"texture\\effect\\skul_head.png",
		5.f, 5.f, 16, m_bIsRight);
	pAttack->SetOwner(this);
	pAttack->CreateProjectile(this, L"SkulHead", Vec2(20, -GetScale().y/2 + 5), Vec2(20, 20), Vec2(700, 0));
	m_pHead = pAttack;
	CREATEOBJECT(pAttack);
}

void CPlayer::SkillB()
{
	SetPos(m_pHead->GetPos());
	m_pHead = nullptr;
}

//void CPlayer::SetCurAnim()
//{
//	CPlayer* pPlayer = this;
//	switch (m_eCurState)
//	{
//	case PLAYER_STATE::IDLE:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_Idle", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Idle_Headless", true);
//	}
//		break;
//	case PLAYER_STATE::MOVE:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_Move", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Move_Headless", true);
//	}
//		break;
//	case PLAYER_STATE::ATTACK:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_AttackA", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_AttackA_Headless", true);
//	}
//		break;
//	case PLAYER_STATE::JUMP:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_Jump", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Jump_Headless", true);
//	}
//		break;
//	case PLAYER_STATE::FALL:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_Fall", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Fall_Headless", true);
//
//	}
//		break;
//	case PLAYER_STATE::SKILL:
//	{
//		pPlayer->GetAnimator()->Play(L"Player_SkillA", true);
//	}
//		break;
//	case PLAYER_STATE::DASH:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_Dash", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Dash_Headless", true);
//	}
//		break;
//	case PLAYER_STATE::JUMPATTACK:
//	{
//		if (pPlayer->m_bCanSkill)
//			pPlayer->GetAnimator()->Play(L"Player_JumpAttack", true);
//		else
//			pPlayer->GetAnimator()->Play(L"Player_Headless_JumpAttack", true);
//	}
//		break;
//	case PLAYER_STATE::REBONE:
//	{
//		pPlayer->GetAnimator()->Play(L"Player_SkillRebone", true);
//	}
//		break;
//	default:
//		break;
//	}
//}

