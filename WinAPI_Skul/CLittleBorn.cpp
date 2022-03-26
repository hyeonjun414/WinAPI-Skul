#include "pch.h"
#include "CLittleBorn.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CPlayerStateIdle.h"
#include "CTile.h"
#include "CBall.h"
#include "CMeleeAttack.h"
#include "CAttack.h"
#include "CEnemy.h"
#include "CUIImage.h"
#include "CUIText.h"

CLittleBorn::CLittleBorn(OBJ_TYPE _eType):
	CPlayer(_eType)
{
}

CLittleBorn::~CLittleBorn()
{
}

void CLittleBorn::Init()
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

	m_eSkulType = SKUL_TYPE::Little_Born;

	SetScale(Vec2(96, 96));
	SetName(L"Player");
	// Collider �����
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y / 4));
	m_pCollider->SetScale(Vec2(GetScale() / 2));

	// �ִϸ����� �����
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

	// �ִϸ������� ��� �ִϸ��̼��� �������� �����Ѵ�.
	m_pAnimator->SetAllAnimOffset(Vec2(0, 30));

	m_pState = new CPlayerStateIdle();
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


	GetPlayerInfo().m_iDamage = 100;
	GetPlayerInfo().m_iHp = 50;
	GetPlayerInfo().m_iMaxHp = 50;
	SINGLE(CGameManager)->m_pCurHealthText->SetText(to_wstring(m_tPlayerInfo.m_iHp) + L" / " + to_wstring(m_tPlayerInfo.m_iMaxHp));
}

void CLittleBorn::Update()
{
	CPlayer::Update();
}

void CLittleBorn::Render()
{
	CPlayer::Render();
}

void CLittleBorn::OnCollision(CCollider* _pOther)
{
	CPlayer::OnCollision(_pOther);
}

void CLittleBorn::OnCollisionEnter(CCollider* _pOther)
{
	CPlayer::OnCollisionEnter(_pOther);
}

void CLittleBorn::OnCollisionExit(CCollider* _pOther)
{
	CPlayer::OnCollisionExit(_pOther);
}

void CLittleBorn::CoolTime()
{
	CPlayer::CoolTime();
}

void CLittleBorn::Attack()
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::PLAYER_ATTACK, this, 0.1f);
	pAttack->CreateAttackArea(this, Vec2(50, 50), Vec2(50, 70));
	CREATEOBJECT(pAttack);
}

void CLittleBorn::JumpAttack()
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::PLAYER_ATTACK, this, 0.1f);
	pAttack->CreateAttackArea(this, Vec2(50, 50), Vec2(50, 70));
	CREATEOBJECT(pAttack);
}

void CLittleBorn::SkillA()
{
	CBall* pAttack = new CBall(OBJ_TYPE::PROJECTILE, this,
		L"Skul_Head", L"texture\\effect\\skul_head.png",
		5.f);
	pAttack->SetVelocity(Vec2(GetObjDir() ? 700.f : -700.f, 0));
	pAttack->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 50.f : -50.f, 0));
	pAttack->SetName(L"SkulHead");
	m_pHead = pAttack;
	CREATEOBJECT(pAttack);
}

void CLittleBorn::SkillB()
{
	if (!m_bCanSkill && nullptr != m_pHead)
	{
		SetPos(m_pHead->GetPos());
		m_pHead = nullptr;
	}
}

void CLittleBorn::Hit(int _damage)
{
	CPlayer::Hit(_damage);
}
