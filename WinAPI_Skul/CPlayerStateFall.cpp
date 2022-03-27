#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateFall::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (pPlayer->IsGround())
		return new CPlayerStateIdle();

	if (KEYTAP(KEY::A) && pPlayer->m_bCanSkill)
	{
		return new CPlayerStateSkillA();
	}
	if (KEYTAP(KEY::S) && !pPlayer->m_bCanSkill)
	{
		return new CPlayerStateSkillB();
	}
	if (KEYTAP(KEY::X) && pPlayer->m_bCanJumpAttack)
	{
		return new CPlayerStateJumpAttack();
	}
	if (KEYTAP(KEY::C) && pPlayer->m_bCanDoubleJump)
	{
		pPlayer->m_bCanDoubleJump = false;
		return new CPlayerStateJump();
	}

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

void CPlayerStateFall::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (KEYHOLD(KEY::LEFT))
		pPlayer->Move(-pPlayer->m_vVelocity.x);
	if (KEYHOLD(KEY::RIGHT))
		pPlayer->Move(pPlayer->m_vVelocity.x);

	pPlayer->m_vVelocity.y += 1400 * DT;
	pPlayer->m_vPos.y += pPlayer->m_vVelocity.y * DT;



	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_vVelocity.y > 200)
		{
			if (pPlayer->m_bCanSkill)
				pPlayer->GetAnimator()->Play(L"LittleBorn_FallRepeat", true);
			else
				pPlayer->GetAnimator()->Play(L"LittleBorn_FallRepeat_Headless", true);
		}
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		if (pPlayer->m_vVelocity.y > 200)
			pPlayer->GetAnimator()->Play(L"Hunter_FallRepeat", true);
		break;
	}
	}
}

void CPlayerStateFall::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"Fall";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_Fall", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_Fall_Headless", true);
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		pPlayer->GetAnimator()->Play(L"Hunter_Fall", true);
		break;
	}
	}
}

void CPlayerStateFall::Exit(CObject* _pObj)
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
