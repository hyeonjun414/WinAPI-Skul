#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CStateIdle.h"
#include "CTile.h"
#include "CProjectile.h"
#include "CMeleeAttack.h"
#include "CAttack.h"
#include "CEnemy.h"
#include "CUIImage.h"
#include "CUIText.h"

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
	SetName(L"Player");
	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y/4));
	m_pCollider->SetScale(Vec2(GetScale()/2));

	// 애니메이터 만들기
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Player_Idle", L"texture\\player\\idle_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_Move", L"texture\\player\\move_skul.png", 0.8f);
	GetAnimator()->CreateAnim(L"Player_Jump", L"texture\\player\\jump_skul.png", 0.2f);
	GetAnimator()->CreateAnim(L"Player_Fall", L"texture\\player\\fall_skul.png", 1.0f);
	GetAnimator()->CreateAnim(L"Player_FallRepeat", L"texture\\player\\fallrepeat_skul.png", 0.3f);
	GetAnimator()->CreateAnim(L"Player_AttackA", L"texture\\player\\attackA_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_AttackB", L"texture\\player\\attackB_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_SkillA", L"texture\\player\\skillA_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_SkillB", L"texture\\player\\skillB_skul.png", 1.0f);
	GetAnimator()->CreateAnim(L"Player_Dash", L"texture\\player\\dash_skul.png", 1.0f);
	GetAnimator()->CreateAnim(L"Player_JumpAttack", L"texture\\player\\jumpattack_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_Idle_Headless", L"texture\\player\\idle_headless_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_Move_Headless", L"texture\\player\\move_headless_skul.png", 0.7f);
	GetAnimator()->CreateAnim(L"Player_Jump_Headless", L"texture\\player\\jump_headless_skul.png", 0.2f);
	GetAnimator()->CreateAnim(L"Player_Fall_Headless", L"texture\\player\\fall_headless_skul.png", 1.0f);
	GetAnimator()->CreateAnim(L"Player_FallRepeat_Headless", L"texture\\player\\fallrepeat_headless_skul.png", 0.3f);
	GetAnimator()->CreateAnim(L"Player_AttackA_Headless", L"texture\\player\\attackA_headless_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_AttackB_Headless", L"texture\\player\\attackB_headless_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_Dash_Headless", L"texture\\player\\dash_headless_skul.png", 1.0f);
	GetAnimator()->CreateAnim(L"Player_JumpAttack_Headless", L"texture\\player\\jumpattack_headless_skul.png", 0.5f);
	GetAnimator()->CreateAnim(L"Player_SkillRebone", L"texture\\player\\skill_rebone_skul.png", 0.5f);

	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset(Vec2(0,30));

	m_pState = new CStateIdle();
	m_pState->Enter(this);

	SINGLE(CSoundManager)->AddSound(L"Jump", L"sound\\Default_Jump.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAir", L"sound\\Default_Jump_Air.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackA", L"sound\\Skul_Atk 1.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackB", L"sound\\Skul_Atk 2.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAttack", L"sound\\Skul_Jump_Atk.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Dash", L"sound\\Default_Dash.wav", false);
	SINGLE(CSoundManager)->AddSound(L"SkillA", L"sound\\Legacy_AttackB.wav", false);
	SINGLE(CSoundManager)->AddSound(L"SkillB", L"sound\\Skul_SkullBack.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Landing", L"sound\\Landing.wav", false);

	
	GetPlayerInfo().m_iDamage = 5;
	GetPlayerInfo().m_iHp = 50;
	GetPlayerInfo().m_iMaxHp = 50;
	SINGLE(CGameManager)->m_pCurHealthText->SetText(to_wstring(m_tPlayerInfo.m_iHp) + L" / " + to_wstring(m_tPlayerInfo.m_iMaxHp));

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
	RenderPlayerInfo();
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
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::MELEE_ATTACK)
	{
		CAttack* pAttack = (CAttack*)_pOther->GetObj();
		CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
		SINGLE(CSoundManager)->Play(L"Hit");
		SINGLE(CGameManager)->CreateEffect(L"Hit", L"texture\\effect\\hit_normal.png",
			(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 0.5f, 0.5f, GetObjDir());
		SINGLE(CGameManager)->DamageText(to_wstring(pEnemy->GetEnemyInfo().m_iDamage),
			(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
		Hit(pEnemy->GetEnemyInfo().m_iDamage);
	}
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PROJECTILE)
	{
		if (L"SkulHead" == _pOther->GetObj()->GetName())
		{
			m_bCanSkill = true;
			m_fSkillCurTime = 0.f;
		}
		else if (L"Wizard_Fireball" == _pOther->GetObj()->GetName())
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
			SINGLE(CGameManager)->CreateEffect(L"Explosion", L"texture\\effect\\explosion_small.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 1.0f, 1.0f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(pEnemy->GetEnemyInfo().m_iDamage),
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
			SINGLE(CSoundManager)->Play(L"Hit");

			Hit(pEnemy->GetEnemyInfo().m_iDamage);
		}
		else if (L"BossBomb" == _pOther->GetObj()->GetName())
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
			SINGLE(CGameManager)->CreateEffect(L"Explosion", L"texture\\effect\\explosion_small.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 1.0f, 1.0f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(pEnemy->GetEnemyInfo().m_iDamage),
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
			SINGLE(CSoundManager)->Play(L"Hit");

			Hit(pEnemy->GetEnemyInfo().m_iDamage);
		}
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

void CPlayer::RenderPlayerInfo()
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
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::PLAYER_ATTACK, this, 0.5f);
	pAttack->CreateAttackArea(this, Vec2(50, 50), Vec2(50, 70));
	CREATEOBJECT(pAttack);

}

void CPlayer::JumpAttack()
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::PLAYER_ATTACK, this, 0.5f);
	pAttack->CreateAttackArea(this, Vec2(50, 50), Vec2(50, 70));
	CREATEOBJECT(pAttack);
}

void CPlayer::SkillA()
{
	CProjectile* pAttack = new CProjectile(OBJ_TYPE::PROJECTILE, this,
		L"Skul_Head", L"texture\\effect\\skul_head.png",
		5.f);
	pAttack->SetVelocity(Vec2(GetObjDir() ? 700.f : -700.f,0));
	pAttack->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 50.f : -50.f, 0));
	pAttack->SetName(L"SkulHead");
	m_pHead = pAttack;
	CREATEOBJECT(pAttack);
}

void CPlayer::SkillB()
{
	if (!m_bCanSkill && nullptr != m_pHead)
	{
		SetPos(m_pHead->GetPos());
		m_pHead = nullptr;
	}
}

void CPlayer::Hit(int _damage)
{
	m_tPlayerInfo.m_iHp = m_tPlayerInfo.m_iHp -_damage < 0 ? 0 : m_tPlayerInfo.m_iHp - _damage;
	Vec2 vec = SINGLE(CGameManager)->m_pCurHealth->GetOriginSize();
	SINGLE(CGameManager)->m_pCurHealth->SetScaleRate(Vec2(vec.x * GetCurHealthRatio(), vec.y));
	SINGLE(CGameManager)->m_pCurHealthText->SetText(to_wstring(m_tPlayerInfo.m_iHp) + L" / " + to_wstring(m_tPlayerInfo.m_iMaxHp));
	
}
