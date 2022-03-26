#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CHunter.h"


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



	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime += DT;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		CHunter* pPlayer = (CHunter*)_pObj;
		m_fCurTime += DT;
		if (m_bOnceFunc)
		{
			if (KEYHOLD(KEY::S) && (0.1f < m_fCurTime && m_fCurTime < 0.2f))
			{
				pPlayer->GetAnimator()->Play(L"Player_AttackReady2", true);
			}
			if (KEYHOLD(KEY::S) && m_fCurTime > 0.2f &&
				!m_bIsAttack)
			{
				m_fDuration += DT;
				pPlayer->m_fCurChargeTime += DT;
				if (pPlayer->m_bCharged)
				{
					pPlayer->GetAnimator()->Play(L"Player_Charge_completed", true);
				}
				else
				{
					pPlayer->GetAnimator()->Play(L"Player_Charging", true);
				}

			}
			if (KEYAWAY(KEY::S) && !m_bIsAttack)
			{
				if (pPlayer->m_bCharged)
					m_fDuration = m_fCurTime + 1.f;
				else
					m_fDuration = m_fCurTime + 0.5f;
				pPlayer->SkillB();
				
				m_fOnceFuncCurTime = 0;
				m_bOnceFunc = false;
				m_bIsAttack = true;
			}
		}

		break;
	}
	}
}

void CPlayerStateSkillB::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"SkillB";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime = 0.f;
		m_fDuration = 0.5f;
		pPlayer->GetAnimator()->Play(L"Player_SkillA", true);
		SINGLE(CSoundManager)->Play(L"SkillA");
		pPlayer->SkillA();
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		m_fDuration = 0.5f;
		m_fCurTime = 0.f;
		m_bOnceFunc = true;
		m_fOnceFuncTime = 0.3f;
		m_fOnceFuncCurTime = 0.f;
		pPlayer->GetAnimator()->Play(L"Player_AttackReady", true);
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
		pPlayer->m_bCanSkill = false;
		pPlayer->m_fSkillCurTime = 0.f;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		break;
	}
	}
}
