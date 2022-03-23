#include "pch.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "Stateheader.h"
#include "CLineObj.h"
#include "CMeleeAttack.h"

CEnemyBoss::CEnemyBoss(OBJ_TYPE _eType, ENEMY_TYPE _eEnemyType):
	CEnemy(_eType, _eEnemyType)
{
	Init();
}

CEnemyBoss::~CEnemyBoss()
{
}

void CEnemyBoss::Init()
{
	switch (m_eEnemyType)
	{
	case ENEMY_TYPE::ELDER_ENT:
	{
		// 个烹 积己
		m_pBody = new CObject(OBJ_TYPE::IMAGE);
		m_pBody->CreateAnimator();
		m_pBody->SetObjDir(true);
		m_pBody->GetAnimator()->CreateAnim(L"BossBody", L"texture\\enemy\\bossbody.png", 10.f);
		m_pBody->GetAnimator()->CreateAnim(L"BossBody_P2", L"texture\\enemy\\bossbody_p2.png", 10.f);
		m_pBody->GetAnimator()->Play(L"BossBody", true);
		CREATEOBJECT(m_pBody);


		// 倔奔 困率 积己
		m_pHeadTop = new CObject(OBJ_TYPE::IMAGE);
		m_pHeadTop->CreateAnimator();
		m_pHeadTop->SetObjDir(true);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop", L"texture\\enemy\\bossface_top.png", 10.f);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop_P2", L"texture\\enemy\\bossface_top_p2.png", 10.f);
		m_pHeadTop->GetAnimator()->Play(L"BossHeadTop", true);
		CREATEOBJECT(m_pHeadTop);

		m_pHeadBottom = new CObject(OBJ_TYPE::IMAGE);
		m_pHeadBottom->CreateAnimator();
		m_pHeadBottom->SetObjDir(true);
		m_pHeadBottom->GetAnimator()->CreateAnim(L"BossHeadBottom", L"texture\\enemy\\bossface_bottom.png", 10.f);
		m_pHeadBottom->GetAnimator()->CreateAnim(L"BossHeadBottom_P2", L"texture\\enemy\\bossface_bottom_p2.png", 10.f);
		m_pHeadBottom->GetAnimator()->Play(L"BossHeadBottom", true);
		CREATEOBJECT(m_pHeadBottom);


		m_pLeftHand = new CObject(OBJ_TYPE::ENEMY);
		m_pLeftHand->CreateAnimator();
		m_pLeftHand->SetObjDir(true);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Idle", L"texture\\enemy\\bosshand.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Slam", L"texture\\enemy\\bosshand_left_slam.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Sweep", L"texture\\enemy\\bosshand_sweep.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Idle_P2", L"texture\\enemy\\bosshand_p2.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Slam_P2", L"texture\\enemy\\bosshand_slam_p2.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Sweep_P2", L"texture\\enemy\\bosshand_sweep_p2.png", 3.f);
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_Bomb", L"texture\\enemy\\bosshand_bomb.png", 3.f);
		m_pLeftHand->GetAnimator()->Play(L"BossLeftHand_Idle", true);
		CREATEOBJECT(m_pLeftHand);

		m_pRightHand = new CObject(OBJ_TYPE::ENEMY);
		m_pRightHand->CreateAnimator();
		m_pRightHand->SetObjDir(false);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Idle", L"texture\\enemy\\bosshand.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Slam", L"texture\\enemy\\bosshand_right_slam.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Sweep", L"texture\\enemy\\bosshand_sweep.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Idle_P2", L"texture\\enemy\\bosshand_p2.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Slam_P2", L"texture\\enemy\\bosshand_slam_p2.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Bomb", L"texture\\enemy\\bosshand_bomb.png", 3.f);
		m_pRightHand->GetAnimator()->Play(L"BossRightHand_Idle", true);
		CREATEOBJECT(m_pRightHand);

		CLineObj* line;
		line = new CLineObj(m_pBody, m_pLeftHand, Vec2(0, 1000), Vec2(0,0), 40.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pRightHand, Vec2(0, 1000), Vec2(0, 0), 40.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pLeftHand, Vec2(0, 500), Vec2(+100, 0), 30.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pRightHand, Vec2(0, 500), Vec2(+100, 0), 40.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pLeftHand, Vec2(500, 500), Vec2(-100, 0), 20.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pRightHand, Vec2(500, 500), Vec2(-100, 0), 40.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pLeftHand, Vec2(-500, 1000), Vec2(100, 0), 34.f);
		CREATEOBJECT(line);
		line = new CLineObj(m_pBody, m_pRightHand, Vec2(-500, 1000), Vec2(100, 0), 28.f);
		CREATEOBJECT(line);
		
		

		SetPos(Vec2(1600.f, 850.f));
		GetEnemyInfo().m_vVelocity = Vec2(0, 300);
		m_fMoveTime = 1.0f;
		m_fMoveCurTime = 0.f;
		m_pState = new CBossStateIdle();
		m_pState->Enter(this);
		SetName(L"Elder_Ent");
		CreateCollider();
		m_pCollider->SetScale(Vec2(200, 450));
		m_pCollider->SetOffsetPos(Vec2(30, 70));
		m_pBody->SetPos(GetPos());
		m_pHeadTop->SetPos(GetPos() + Vec2(0, -50));
		m_pHeadBottom->SetPos(GetPos() + Vec2(30, 70));
		m_pLeftHand->SetPos(GetPos() + Vec2(-280, 100));
		m_pRightHand->SetPos(GetPos() + Vec2(+280, 100));

		SINGLE(CSoundManager)->AddSound(L"BossSlam", L"sound\\ElderEnt_FistSlam.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossSweep", L"sound\\ElderEnt_Sweeping.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossSweepRoar", L"sound\\ElderEnt_Sweeping_Roar.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossRoar", L"sound\\ElderEnt_Roar.wav", false);
		

	}
		break;
	}
}

void CEnemyBoss::Update()
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


	if (nullptr != m_pAnimator)
		m_pAnimator->Update();

}

void CEnemyBoss::Render()
{
	CEnemy::Render();
}

void CEnemyBoss::OnCollision(CCollider* _pOther)
{
}

void CEnemyBoss::OnCollisionEnter(CCollider* _pOther)
{
}

void CEnemyBoss::OnCollisionExit(CCollider* _pOther)
{
}

void CEnemyBoss::Slam(CObject* _pObj)
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::BOSS_ATTACK, _pObj, 0.5f);
	pAttack->CreateAttackArea(_pObj, Vec2(0, 0), Vec2(200, 200));
	pAttack->SetName(L"Slam");
	CREATEOBJECT(pAttack);
}

void CEnemyBoss::Sweep(CObject* _pObj)
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::BOSS_ATTACK, _pObj, 1.0f);
	pAttack->CreateAttackArea(_pObj, Vec2(0, 0), Vec2(170, 250));
	pAttack->SetName(L"Sweep");

	CREATEOBJECT(pAttack);
	SINGLE(CCameraManager)->CameraShaking(2000, 1.f);
	SINGLE(CSoundManager)->Play(L"BossSweep");
	SINGLE(CSoundManager)->Play(L"BossSweepRoar");
}
