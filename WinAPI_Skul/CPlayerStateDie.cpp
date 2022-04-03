#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CGameOverUI.h"

CPlayerState* CPlayerStateDie::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	if (m_fCurTime >= m_fDuration)
	{
		SINGLE(CGameManager)->SetGamePlay(false);
		CGameOverUI* pGameOver = new CGameOverUI();
		pGameOver->Init();
		CREATEOBJECT(pGameOver);
	}

	return nullptr;
}

void CPlayerStateDie::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	m_fCurTime += DT;
}

void CPlayerStateDie::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	m_fDuration = 1.2f;
	m_fCurTime = 0.f;
	pPlayer->GetAnimator()->Play(L"LittleBorn_Die", false);
}

void CPlayerStateDie::Exit(CObject* _pObj)
{
}
