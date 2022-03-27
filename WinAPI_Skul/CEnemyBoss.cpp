#include "pch.h"
#include "CEnemyBoss.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "Stateheader.h"
#include "CLineObj.h"
#include "CMeleeAttack.h"
#include "CPlayer.h"
#include "CUIImage.h"
#include "CObjGenerator.h"
#include "CSfx.h"
#include "CVfx.h"
#include "CBall.h"

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
		m_pBody->GetAnimator()->CreateAnim(L"BossBody_End", L"texture\\enemy\\bossbody_end.png", 10.f);
		m_pBody->GetAnimator()->Play(L"BossBody", true);
		CREATEOBJECT(m_pBody);


		// 倔奔 困率 积己
		m_pHeadTop = new CObject(OBJ_TYPE::IMAGE);
		m_pHeadTop->CreateAnimator();
		m_pHeadTop->SetObjDir(true);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop", L"texture\\enemy\\bossface_top.png", 10.f);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop_P2", L"texture\\enemy\\bossface_top_p2.png", 10.f);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop_Die", L"texture\\enemy\\bossface_top_die.png", 10.f);
		m_pHeadTop->GetAnimator()->CreateAnim(L"BossHeadTop_End", L"texture\\enemy\\bossface_top_end.png", 10.f);
		m_pHeadTop->GetAnimator()->Play(L"BossHeadTop", true);
		CREATEOBJECT(m_pHeadTop);

		m_pHeadBottom = new CObject(OBJ_TYPE::IMAGE);
		m_pHeadBottom->CreateAnimator();
		m_pHeadBottom->SetObjDir(true);
		m_pHeadBottom->GetAnimator()->CreateAnim(L"BossHeadBottom", L"texture\\enemy\\bossface_bottom.png", 10.f);
		m_pHeadBottom->GetAnimator()->CreateAnim(L"BossHeadBottom_P2", L"texture\\enemy\\bossface_bottom_p2.png", 10.f);
		m_pHeadBottom->GetAnimator()->CreateAnim(L"BossHeadBottom_End", L"texture\\enemy\\bossface_bottom_end.png", 10.f);
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
		m_pLeftHand->GetAnimator()->CreateAnim(L"BossLeftHand_End", L"texture\\enemy\\bosshands_end.png", 3.f);
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
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Sweep_P2", L"texture\\enemy\\bosshand_sweep_p2.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_Bomb", L"texture\\enemy\\bosshand_bomb.png", 3.f);
		m_pRightHand->GetAnimator()->CreateAnim(L"BossRightHand_End", L"texture\\enemy\\bosshands_end.png", 3.f);
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
		
		m_fHitDelayTime = 0.1f;
		m_fCurHitTime = 0.f;
		m_bCanHit = true;
		SetPos(Vec2(1600.f, 800.f));
		tEnemy_Info& info = GetEnemyInfo();
		info.m_vVelocity = Vec2(0, 400);
		info.m_iHp = 2000;
		info.m_iMaxHp = info.m_iHp;
		info.m_iDamage = 5;
		
		m_fMoveTime = 1.0f;
		m_fMoveCurTime = 0.f;
	
		SetName(L"Elder_Ent");
		CreateCollider();
		m_pCollider->SetScale(Vec2(200, 450));
		m_pCollider->SetOffsetPos(Vec2(30, 70));

		m_pBody->SetPos(GetPos() + Vec2(0,50));
		m_pHeadTop->SetPos(GetPos() + Vec2(0, 0));
		m_pHeadBottom->SetPos(GetPos() + Vec2(30, 120));
		m_pLeftHand->SetPos(GetPos() + Vec2(-350, 180));
		m_pRightHand->SetPos(GetPos() + Vec2(+350, 180));

		m_pState = new CBossStateIdle();
		m_pState->Enter(this);

		

		SINGLE(CSoundManager)->AddSound(L"BossSlam", L"sound\\ElderEnt_FistSlam.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossSweep", L"sound\\ElderEnt_Sweeping.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossSweepRoar", L"sound\\ElderEnt_Sweeping_Roar.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossRoar", L"sound\\ElderEnt_Roar.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossBombFire", L"sound\\ElderEnt_EnergyBomb_Fire.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossBombReady", L"sound\\ElderEnt_EnergyBomb_Ready.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossBombExplosion", L"sound\\Atk_Explosion_Small.wav", false);
		SINGLE(CSoundManager)->AddSound(L"BossChangeIntro", L"sound\\ElderEnt_Change_Intro.wav", false);
		

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
	//CEnemy::OnCollisionEnter(_pOther);
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER_ATTACK)
	{
		CMeleeAttack* pAttack = (CMeleeAttack*)_pOther->GetObj();

		if (m_bCanHit && m_strCurState != L"Change" && m_strCurState != L"Die")
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CPlayer* pPlayer = (CPlayer*)pAttack->GetOwner();
			int damage = SINGLE(CGameManager)->RandomInt(pPlayer->GetPlayerInfo().m_iDamage, 0.2f);
			SINGLE(CSoundManager)->Play(L"Hit");
			SINGLE(CGameManager)->CreateVfx(L"Hit", L"texture\\effect\\hit_normal.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 0.5f, 0.5f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(damage), (m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2);
			Hit(damage);
			m_bCanHit = false;
		}
	}
}

void CEnemyBoss::OnCollisionExit(CCollider* _pOther)
{
}

void CEnemyBoss::Hit(int _damage)
{
	m_tEnemyInfo.m_iHp = m_tEnemyInfo.m_iHp - _damage < 0 ? 0 : m_tEnemyInfo.m_iHp - _damage;
	Vec2 vec = SINGLE(CGameManager)->m_pBossStatus->GetOriginSize();
	SINGLE(CGameManager)->m_pBossStatus->SetScaleRate(Vec2(vec.x * m_tEnemyInfo.m_iHp/(float)m_tEnemyInfo.m_iMaxHp, vec.y));

}

void CEnemyBoss::Slam(CObject* _pObj)
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::MELEE_ATTACK, this, 0.5f);
	pAttack->CreateAttackArea(_pObj, Vec2(0, 0), Vec2(200, 200));
	pAttack->SetTraceObj(_pObj);
	pAttack->SetName(L"Slam");
	CREATEOBJECT(pAttack);
}

void CEnemyBoss::Sweep(CObject* _pObj)
{
	CMeleeAttack* pAttack = new CMeleeAttack(OBJ_TYPE::MELEE_ATTACK, this, 1.0f);
	pAttack->CreateAttackArea(_pObj, Vec2(0, 0), Vec2(170, 250));
	pAttack->SetTraceObj(_pObj);
	pAttack->SetName(L"Sweep");

	CREATEOBJECT(pAttack);
	SINGLE(CCameraManager)->CameraShaking(2000, 1.f);
	SINGLE(CSoundManager)->Play(L"BossSweep");
	SINGLE(CSoundManager)->Play(L"BossSweepRoar");
}

void CEnemyBoss::EnergyBomb()
{
	//CObject* pObj = m_pHeadTop;
	//Vec2 startPos = pObj->GetPos() + Vec2(rand() % 1400 - 700, rand() % 50 - 25) + Vec2(0, -100);
	////Vec2 vVelo = (PLAYERPOS - startPos).Normalize() * 300;
	//
	//SINGLE(CGameManager)->CreateVfx(L"Bomb_Emerge", L"texture\\effect\\ElderEntP2_EnergyCorps_Projectile_Emerge.png",
	//	startPos, 1.f, 1.f, true, 1.f);
	//CBall* pProj = new CBall(OBJ_TYPE::PROJECTILE, pObj,
	//	L"BossBomb", L"texture\\effect\\ElderEntP2_EnergyCorps_Projectile.png",
	//	5.f);
	//Vec2 vVelo = Vec2(rand() % 500 - 250, 500);
	//pProj->SetVelocity(vVelo);
	//CREATEOBJECT(pProj);
	//SINGLE(CSoundManager)->Play(L"BossBombReady");

	//CObjGenerator* pObjGene = new CObjGenerator(0.1f, GetPos() + Vec2(0, -100), Vec2(rand() % 1400 - 700, rand() % 50 - 25), 1.f);
	//for (int i = 1; i <= 20; i++)
	//{
	//	CBall* pProj = new CBall(OBJ_TYPE::PROJECTILE, pObj,
	//		L"BossBomb", L"texture\\effect\\ElderEntP2_EnergyCorps_Projectile.png",
	//		5.f);
	//	Vec2 vVelo = Vec2(rand() % 500 - 250, 500);
	//	pProj->SetVelocity(vVelo);
	//	pObjGene->ReservateObj(pProj);

	//	CSfx* pSfx = new CSfx(L"Arrow");
	//	pObjGene->ReservateSfx(pSfx);
	//}
	//CREATEOBJECT(pObjGene);
}
