#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateMove::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (KEYTAP(KEY::SPACE) && nullptr != SINGLE(CGameManager)->m_pPlayer2)
	{
		SWITCHSKUL;
		SINGLE(CGameManager)->CreateVfx(L"Switch_Skul", L"texture\\effect\\Switch_Skul.png",
			_pObj->GetCollider()->GetFinalPos(), 0.5f, 0.5f, _pObj->GetObjDir());
		SINGLE(CSoundManager)->Play(L"Switch");
	}

	if (pPlayer->GetPlayerInfo().m_iHp <= 0)
	{
		return new CPlayerStateDie();
	}


	if (KEYAWAY(KEY::LEFT) || KEYAWAY(KEY::RIGHT))
	{
		return new CPlayerStateIdle();
	}
	if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
	{
		return new CPlayerStateSkillA();
	}
	if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
	{
		return new CPlayerStateSkillB();
	}
	if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
	{
		
		return new CPlayerStateDash();
	}
	if (KEYTAP(KEY::X))
	{
		return new CPlayerStateAttack();
	}
	if (KEYTAP(KEY::C))
	{
		return new CPlayerStateJump();
	}
	if (!pPlayer->IsGround())
		return new CPlayerStateFall();


	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
	return nullptr;
}

void CPlayerStateMove::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (KEYHOLD(KEY::LEFT))
		pPlayer->Move(-pPlayer->m_vVelocity.x);
	if (KEYHOLD(KEY::RIGHT))
		pPlayer->Move(pPlayer->m_vVelocity.x);

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}

void CPlayerStateMove::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"Move";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_Move", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_Move_Headless", true);
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		pPlayer->GetAnimator()->Play(L"Hunter_Move", true);
		break;
	}
	}
}

void CPlayerStateMove::Exit(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}
