#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateDash::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (m_iCurMoveDist >= m_iDist)
		return new CPlayerStateIdle();

	if (KEYTAP(KEY::Z) && pPlayer->m_bCanSecondDash)
	{
		pPlayer->m_bCanSecondDash = false;
		return new CPlayerStateDash();
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

void CPlayerStateDash::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (pPlayer->m_bIsRight)
		pPlayer->m_vPos.x += m_fDashSpeed * DT;
	else
		pPlayer->m_vPos.x -= m_fDashSpeed * DT;

	m_iCurMoveDist += m_fDashSpeed * DT;

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

void CPlayerStateDash::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	m_iDist = 200;
	m_iCurMoveDist = 0;
	m_fDashSpeed = 700;

	pPlayer->m_vPos.y -= 1;
	pPlayer->m_vVelocity.y = 0;

	pPlayer->m_strCurState = L"Dash";
	SINGLE(CGameManager)->CreateEffect(L"Dash_Smoke", L"texture\\effect\\dash_smoke_midium.png",
		pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());
	SINGLE(CSoundManager)->Play(L"Dash");


	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"Player_Dash", true);
		else
			pPlayer->GetAnimator()->Play(L"Player_Dash_Headless", true);
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		pPlayer->GetAnimator()->Play(L"Player_Dash", true);
		break;
	}
	}
}

void CPlayerStateDash::Exit(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_bCanDash = false;
	pPlayer->m_fDashCurTime = 0;

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
