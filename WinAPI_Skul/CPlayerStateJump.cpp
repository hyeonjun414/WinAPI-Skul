#include "pch.h"

#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CHunter.h"

CPlayerState* CPlayerStateJump::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (pPlayer->GetPlayerInfo().m_iHp <= 0)
	{
		return new CPlayerStateDie();
	}

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
		{
			return new CPlayerStateSkillA();
		}
		if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
		{
			return new CPlayerStateSkillB();
		}
		if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
		{
			pPlayer->m_bCanDoubleJump = false;
			return new CPlayerStateJump();
		}
		if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
		{
			pPlayer->m_bCanDash = false;
			return new CPlayerStateDash();
		}
		if (KEYTAP(KEY::X) && pPlayer->m_bCanJumpAttack)
		{
			return new CPlayerStateJumpAttack();
		}
		if (pPlayer->GetVelocity().y >= 0)
			return new CPlayerStateFall();
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
		{
			pPlayer->m_bCanDoubleJump = false;
			return new CPlayerStateJump();
		}
		if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
		{
			pPlayer->m_bCanDash = false;
			return new CPlayerStateDash();
		}
		if (KEYTAP(KEY::X) && pPlayer->m_bCanJumpAttack)
		{
			return new CPlayerStateJumpAttack();
		}
		if (pPlayer->GetVelocity().y >= 0)
			return new CPlayerStateFall();
		break;
	}
	}
	return nullptr;
}

void CPlayerStateJump::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	// 좌우 이동
	if (KEYHOLD(KEY::LEFT))
		pPlayer->Move(-pPlayer->m_vVelocity.x);
	if (KEYHOLD(KEY::RIGHT))
		pPlayer->Move(pPlayer->m_vVelocity.x);

	// 중력 적용
	pPlayer->m_vVelocity.y += 1400 * DT;
	pPlayer->m_vPos.y += pPlayer->m_vVelocity.y * DT;

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

void CPlayerStateJump::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"Jump";
	pPlayer->m_vVelocity.y = -700;

	if (!pPlayer->m_bCanDoubleJump)
	{
		SINGLE(CGameManager)->CreateVfx(L"Jump_Smoke", L"texture\\effect\\doublejump_smoke.png",
			pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());
		SINGLE(CSoundManager)->Play(L"JumpAir");
	}
	else
	{
		SINGLE(CSoundManager)->Play(L"Jump");
	}

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_Jump", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_Jump_Headless", true);
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		CHunter* pPlayer = (CHunter*)_pObj;
		pPlayer->GetAnimator()->Play(L"Hunter_Jump", true);
		break;
	}
	}
}

void CPlayerStateJump::Exit(CObject* _pObj)
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

