#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateSkillB::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (m_fCurTime >= m_fDuration)
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

void CPlayerStateSkillB::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	m_fCurTime += DT;

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

void CPlayerStateSkillB::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	SINGLE(CSoundManager)->Play(L"SkillB");

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime = 0.f;
		m_fDuration = 0.5f;

		SINGLE(CGameManager)->CreateEffect(L"DisAppear", L"texture\\effect\\Enemy_Dead.png",
			pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());

		pPlayer->SkillB();

		SINGLE(CGameManager)->CreateEffect(L"Appear", L"texture\\effect\\Enemy_Appearance.png",
			pPlayer->GetPos(), 0.5f, 0.5f, pPlayer->GetObjDir());

		pPlayer->GetAnimator()->Play(L"Player_SkillRebone", true);

		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}

void CPlayerStateSkillB::Exit(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		pPlayer->m_vVelocity.y = 0;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}
