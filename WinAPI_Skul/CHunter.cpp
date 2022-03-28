#include "pch.h"
#include "CHunter.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CPlayerStateIdle.h"
#include "CTile.h"
#include "CProjectile.h"
#include "CMeleeAttack.h"
#include "CAttack.h"
#include "CEnemy.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CArrow.h"
#include "CObjGenerator.h"
#include "CSfx.h"

CHunter::CHunter(OBJ_TYPE _eType):
	CPlayer(_eType)
{
}

CHunter::~CHunter()
{

}

void CHunter::Init()
{
	

	SetScale(Vec2(96, 96));
	SetName(L"Player");
	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y / 4));
	m_pCollider->SetScale(Vec2(GetScale() / 2));

	// 애니메이터 만들기
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Hunter_Idle", L"texture\\player\\hunter\\hunter_idle.png", 0.5f);
	GetAnimator()->CreateAnim(L"Hunter_Move", L"texture\\player\\hunter\\hunter_move.png", 0.8f);
	GetAnimator()->CreateAnim(L"Hunter_Jump", L"texture\\player\\hunter\\hunter_jump.png", 0.2f);
	GetAnimator()->CreateAnim(L"Hunter_Fall", L"texture\\player\\hunter\\hunter_fall.png", 1.0f);
	GetAnimator()->CreateAnim(L"Hunter_FallRepeat", L"texture\\player\\hunter\\hunter_fallrepeat.png", 0.3f);
	GetAnimator()->CreateAnim(L"Hunter_Dash", L"texture\\player\\hunter\\hunter_dash.png", 1.f);
	GetAnimator()->CreateAnim(L"Hunter_AttackReady", L"texture\\player\\hunter\\hunter_chargeshot_anticipation.png", 0.1f);
	GetAnimator()->CreateAnim(L"Hunter_AttackReady2", L"texture\\player\\hunter\\hunter_chargeshot_prepare.png", 0.1f);
	GetAnimator()->CreateAnim(L"Hunter_Attack", L"texture\\player\\hunter\\hunter_fastshot_attack.png", 0.3f);
	GetAnimator()->CreateAnim(L"Hunter_JumpAttack", L"texture\\player\\hunter\\hunter_jumpattack.png", 0.3f);
	GetAnimator()->CreateAnim(L"Hunter_Charging", L"texture\\player\\hunter\\hunter_chargeshot_charging.png", 0.2f);
	GetAnimator()->CreateAnim(L"Hunter_Charged", L"texture\\player\\hunter\\hunter_chargeshot_charged.png", 0.2f);
	GetAnimator()->CreateAnim(L"Hunter_Charge_completed", L"texture\\player\\hunter\\hunter_chargeshot_charge_complated.png", 1.f);

	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset(Vec2(0, 30));

	SINGLE(CSoundManager)->AddSound(L"Jump", L"sound\\Default_Jump.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAir", L"sound\\Default_Jump_Air.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackA", L"sound\\Skul_Atk 1.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackB", L"sound\\Skul_Atk 2.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAttack", L"sound\\Skul_Jump_Atk.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Dash", L"sound\\Default_Dash.wav", false);
	SINGLE(CSoundManager)->AddSound(L"SkillA", L"sound\\Legacy_AttackB.wav", false);
	SINGLE(CSoundManager)->AddSound(L"SkillB", L"sound\\Skul_SkullBack.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Landing", L"sound\\Landing.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Arrow", L"sound\\Shot_Arrow.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Switch", L"sound\\Default_Switch.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Hunter_Charge_Completed", L"sound\\Hunter_Charge_Completed.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Hunter_DrawArrow", L"sound\\Hunter_DrawArrow.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Hunter_SkillA_Fire", L"sound\\Hunter_SkillA_Impact2.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Hunter_SkillB_Arrow", L"sound\\Hunter_SkillB_Arrow.wav", false);



	m_pState = new CPlayerStateIdle();
	m_pState->Enter(this);


	GetPlayerInfo().m_iDamage = 100;
	GetPlayerInfo().m_iHp = 50;
	GetPlayerInfo().m_iMaxHp = 50;

	Enter();
	

}

void CHunter::Update()
{
	CPlayer::Update();
}

void CHunter::Render()
{
	CPlayer::Render();
}

void CHunter::OnCollision(CCollider* _pOther)
{
	CPlayer::OnCollision(_pOther);
}

void CHunter::OnCollisionEnter(CCollider* _pOther)
{
	CPlayer::OnCollisionEnter(_pOther);

}

void CHunter::OnCollisionExit(CCollider* _pOther)
{
	CPlayer::OnCollisionExit(_pOther);

}

void CHunter::CoolTime()
{
	CPlayer::CoolTime();
	if (m_fCurChargeTime >= m_fChargeTime)
		m_bCharged = true;
}

void CHunter::Attack()
{
	SINGLE(CSoundManager)->Play(L"Arrow");
	if (m_bCharged)
	{
		m_fCurChargeTime = 0.f;
		m_bCharged = false;
		GetAnimator()->Play(L"Hunter_Attack", true);
		CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
			L"Arrow_completed", L"texture\\player\\hunter\\Hunter_Attack_Completed_Projectile.png", 5.f);
		pProj->SetVelocity(Vec2(GetObjDir() ? 2000.f : -2000.f, -100.f));
		pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
		CREATEOBJECT(pProj);
	}
	else
	{
		m_fCurChargeTime = 0.f;
		GetAnimator()->Play(L"Hunter_Attack", true);
		CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
			L"Arrow_Incompleted", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile.png", 5.f);
		pProj->SetVelocity(Vec2(GetObjDir() ? 1400.f : -1400.f, -150.f));
		pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
		CREATEOBJECT(pProj);
	}
}

void CHunter::JumpAttack()
{
	SINGLE(CSoundManager)->Play(L"Arrow");
	m_fCurChargeTime = 0.f;
	GetAnimator()->Play(L"Hunter_JumpAttack", true);
	CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
		L"Arrow_Incompleted", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile.png", 5.f);
	pProj->SetVelocity(Vec2(GetObjDir() ? 1400.f : -1400.f, -150.f));
	pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
	CREATEOBJECT(pProj);
}

void CHunter::SkillA()
{

	if (m_bCharged)
	{
		SINGLE(CSoundManager)->Play(L"Hunter_SkillA_Fire");
		m_fCurChargeTime = 0.f;
		m_bCharged = false;
		GetAnimator()->Play(L"Hunter_Attack", true);
		CObjGenerator* pObjGene = new CObjGenerator(0.1f, GetPos()+Vec2(GetObjDir()? 500 : -500, -500), Vec2(500, 50), 1.f);
		for (int i = 1; i <= 10; i++)
		{
			CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
				L"Arrow_completed", L"texture\\player\\hunter\\Hunter_Attack_Completed_Projectile.png", 5.f);
			pProj->SetName(L"ArrowRain");
			pProj->SetVelocity(Vec2(0, 1400.f));
			pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
			pObjGene->ReservateObj(pProj);

			CSfx* pSfx = new CSfx(L"Arrow");
			pObjGene->ReservateSfx(pSfx);
		}
		CREATEOBJECT(pObjGene);
		SINGLE(CGameManager)->CreateVfx(L"ArrowRainFire", L"texture\\effect\\Hunter_SiegeShot_Charged.png",
				m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 30 : -30, -60), 0.5f, 0.5f, GetObjDir());
	}
	else
	{
		SINGLE(CSoundManager)->Play(L"Arrow");
		m_fCurChargeTime = 0.f;
		GetAnimator()->Play(L"Hunter_Attack", true);
		for (int i = 1; i <= 5; i++)
		{
			CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
				L"Arrow_Incompleted", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile.png", 5.f);
			float theta = 60 + i * 5;
			float angle = DEG(theta);
			Vec2 velo = Vec2(GetObjDir()? cosf(angle) : -cosf(angle), -sinf(angle));
			pProj->SetName(L"ArrowRain");
			pProj->SetVelocity(velo*800);
			pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));

			CREATEOBJECT(pProj);
		}
	}
}

void CHunter::SkillB()
{
	if (m_bCharged)
	{
		m_fCurChargeTime = 0.f;
		m_bCharged = false;
		GetAnimator()->Play(L"Hunter_Attack", true);
		CObjGenerator* pObjGene = new CObjGenerator(0.1f, GetPos() + Vec2(GetObjDir() ? 70 : -70, -30), Vec2(10, 20));
		for (int i = 1; i <= 10; i++)
		{
			CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
				L"Arrow_completed", L"texture\\player\\hunter\\Hunter_Attack_Completed_Projectile.png", 5.f);
			pProj->SetVelocity(Vec2(GetObjDir() ? 2000.f : -2000.f, -120.f));
			pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
			pObjGene->ReservateObj(pProj);

			CSfx* pSfx = new CSfx(L"Hunter_SkillB_Arrow");
			pObjGene->ReservateSfx(pSfx);
		}
		CREATEOBJECT(pObjGene);
		SINGLE(CGameManager)->CreateVfx(L"RapidShotEffect", L"texture\\effect\\Hunter_RapidShot_Completed.png",
			m_pCollider->GetFinalPos()+ Vec2(GetObjDir()?50:-50, -10), 1.f, 1.f, GetObjDir());

	}
	else
	{
		m_fCurChargeTime = 0.f;
		m_bCharged = false;
		GetAnimator()->Play(L"Hunter_Attack", true);
		CObjGenerator* pObjGene = new CObjGenerator(0.1f, GetPos() + Vec2(GetObjDir() ? 50 : -50, -30), Vec2(10, 20));
		for (int i = 1; i <= 5; i++)
		{
			CArrow* pProj = new CArrow(OBJ_TYPE::PLAYER_ATTACK, this,
				L"Arrow_Incompleted", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile.png", 5.f);
			pProj->SetVelocity(Vec2(GetObjDir() ? 1400.f : -1400.f, -150.f));
			pProj->SetPos(m_pCollider->GetFinalPos() + Vec2(GetObjDir() ? 25.f : -25.f, 0));
			pObjGene->ReservateObj(pProj);

			CSfx* pSfx = new CSfx(L"Hunter_SkillB_Arrow");
			pObjGene->ReservateSfx(pSfx);
		}
		CREATEOBJECT(pObjGene);
	}
}

void CHunter::Hit(int _damage)
{
	CPlayer::Hit(_damage);
}

void CHunter::Enter()
{
	SetActive(true);
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

	m_bCharged = false;
	m_fChargeTime = 1.f;
	m_fCurChargeTime = 0.f;


	m_eSkulType = SKUL_TYPE::Hunter;

	SINGLE(CGameManager)->m_pCurHealthText->SetText(to_wstring(m_tPlayerInfo.m_iHp) + L" / " + to_wstring(m_tPlayerInfo.m_iMaxHp));
	Vec2 vec = SINGLE(CGameManager)->m_pCurHealth->GetOriginSize();
	SINGLE(CGameManager)->m_pCurHealth->SetScaleRate(Vec2(vec.x * GetCurHealthRatio(), vec.y));

	SINGLE(CGameManager)->m_pPortrait->SetImage(L"Portrait_Hunter", L"texture\\icon\\Hunter.png");
	SINGLE(CGameManager)->m_pSkillA->SetImage(L"SkillA_Hunter", L"texture\\icon\\SiegeShot.png");
	SINGLE(CGameManager)->m_pSkillB->SetImage(L"SkillB_Hunter", L"texture\\icon\\ImmovableShot.png");

}

void CHunter::Exit()
{
	SetActive(false);
	SINGLE(CGameManager)->m_pSubSkul->SetImage(L"Portrait_Hunter", L"texture\\icon\\Hunter.png");
	SINGLE(CGameManager)->m_pSubSkillA->SetImage(L"SkillA_Hunter", L"texture\\icon\\SiegeShot.png");
	SINGLE(CGameManager)->m_pSubSkillB->SetImage(L"SkillB_Hunter", L"texture\\icon\\ImmovableShot.png");
}
