#include "pch.h"

#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CHunter.h"

CPlayerState* CPlayerStateSkillA::HandleInput(CObject* _pObj)
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

void CPlayerStateSkillA::Update(CObject* _pObj)
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
			if (KEYHOLD(KEY::A) && (0.1f < m_fCurTime && m_fCurTime < 0.2f))
			{
				pPlayer->GetAnimator()->Play(L"Hunter_AttackReady2", true);
			}
			if (KEYHOLD(KEY::A) && m_fCurTime > 0.2f &&
				!m_bIsAttack)
			{
				m_fDuration += DT;
				pPlayer->m_fCurChargeTime += DT;
				if (pPlayer->m_bCharged)
				{
					pPlayer->GetAnimator()->Play(L"Hunter_Charge_completed", true);
				}
				else
				{
					pPlayer->GetAnimator()->Play(L"Hunter_Charging", true);
				}

			}
			if (KEYAWAY(KEY::A) && !m_bIsAttack)
			{
				pPlayer->SkillA();
				m_fOnceFuncCurTime = 0;
				m_bOnceFunc = false;
				m_bIsAttack = true;
			}
		}

		break;
	}
	}
}

void CPlayerStateSkillA::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"SkillA";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fCurTime = 0.f;
		m_fDuration = 0.5f;
		pPlayer->GetAnimator()->Play(L"LittleBorn_SkillA", true);
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
		pPlayer->GetAnimator()->Play(L"Hunter_AttackReady", true);
		break;
	}
	}
}

void CPlayerStateSkillA::Exit(CObject* _pObj)
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
