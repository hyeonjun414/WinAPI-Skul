#include "pch.h"

#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateJumpAttack::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (pPlayer->GetPlayerInfo().m_iHp <= 0)
	{
		return new CPlayerStateDie();
	}

	if (m_fCurTime >= m_fDuration ||
		pPlayer->m_bIsGround)
		return new CPlayerStateIdle();

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

void CPlayerStateJumpAttack::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	m_fCurTime += DT;




	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (KEYHOLD(KEY::LEFT))
			pPlayer->Move(-pPlayer->m_vVelocity.x);
		if (KEYHOLD(KEY::RIGHT))
			pPlayer->Move(pPlayer->m_vVelocity.x);

		pPlayer->m_vVelocity.y += 1400 * DT;
		pPlayer->m_vPos.y += pPlayer->m_vVelocity.y * DT;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}

void CPlayerStateJumpAttack::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	
	pPlayer->m_bCanJumpAttack = false;
	pPlayer->m_strCurState = L"JumpAttack";
	SINGLE(CSoundManager)->Play(L"AttackB");

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fDuration = 0.5f;
		m_fCurTime = 0.f;
		pPlayer->JumpAttack();
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_JumpAttack", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_JumpAttack_Headless", true);
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		m_fDuration = 0.3f;
		m_fCurTime = 0.f;
		pPlayer->JumpAttack();
		pPlayer->GetAnimator()->Play(L"Hunter_JumpAttack", true);
		SINGLE(CSoundManager)->Play(L"Hunter_DrawArrow");
		break;
	}
	}
}

void CPlayerStateJumpAttack::Exit(CObject* _pObj)
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
		pPlayer->m_vVelocity.y = 0;
		break;
	}
	}
}
