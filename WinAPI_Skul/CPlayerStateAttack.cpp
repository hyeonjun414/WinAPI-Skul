#include "pch.h"

#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CHunter.h"

CPlayerState* CPlayerStateAttack::HandleInput(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;



	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		// 공격 시간이 종료되었거나, 마지막 모션이 끝났을때
		if (m_fAttackTime <= 0 || m_iAttackCount == 2)
			return new CPlayerStateIdle();

		if (KEYTAP(KEY::X))
			m_bAttackInput = true;
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		if (m_fCurTime >= m_fDuration)
			return new CPlayerStateIdle();
		break;
	}
	}
	return nullptr;
}

void CPlayerStateAttack::Update(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;


	if (!m_bOnceFunc)
	{
		m_fOnceFuncCurTime += DT;
		if (m_fOnceFuncCurTime >= m_fOnceFuncTime)
		{
			m_bOnceFunc = true;
			m_fOnceFuncCurTime = 0.f;
		}
	}
	


	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fAttackCurTime += DT;
		m_fAttackTime -= DT;
		if (m_fAttackCurTime >= m_fAttackDelay && m_bAttackInput)
		{
			m_fAttackCurTime = 0;
			m_iAttackCount++;
			m_bAttackInput = false;
			m_fAttackTime += m_fAttackDelay;
		}

		if (1 == m_iAttackCount && !m_bIsSecondAttack)
		{
			m_bIsSecondAttack = true;
			if (pPlayer->m_bCanSkill)
				pPlayer->GetAnimator()->Play(L"LittleBorn_AttackB", true);
			else
				pPlayer->GetAnimator()->Play(L"LittleBorn_AttackB_Headless", true);
			SINGLE(CSoundManager)->Play(L"AttackB");

			if (KEYHOLD(KEY::LEFT))
			{
				pPlayer->m_bIsRight = false;
				pPlayer->m_vPos.x -= 30;
			}
			if (KEYHOLD(KEY::RIGHT))
			{
				pPlayer->m_bIsRight = true;
				pPlayer->m_vPos.x += 30;
			}
			pPlayer->Attack();
		}
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		CHunter* pPlayer = (CHunter*)_pObj;
		m_fCurTime += DT;
		if (m_bOnceFunc)
		{
			if (KEYHOLD(KEY::X) && (0.1f < m_fCurTime && m_fCurTime < 0.2f))
			{
				pPlayer->GetAnimator()->Play(L"Hunter_AttackReady2", true);
			}
			if (KEYHOLD(KEY::X) && m_fCurTime > 0.2f &&
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
			if (KEYAWAY(KEY::X) && !m_bIsAttack)
			{
				pPlayer->Attack();
				m_fOnceFuncCurTime = 0;
				m_bOnceFunc = false;
				m_bIsAttack = true;
			}
		}

		break;
	}
	}
}

void CPlayerStateAttack::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;

	pPlayer->m_strCurState = L"Attack";

	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		m_fAttackDelay = 0.5f;
		m_fAttackTime = m_fAttackDelay;
		m_iAttackCount = 0;
		m_fCurTime = 0;
		m_bIsSecondAttack = false;
		m_bAttackInput = false;
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_AttackA", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_AttackA_Headless", true);
		SINGLE(CSoundManager)->Play(L"AttackA");
		
		if (KEYHOLD(KEY::LEFT))
		{
			pPlayer->m_bIsRight = false;
			pPlayer->m_vPos.x -= 20;
		}
		if (KEYHOLD(KEY::RIGHT))
		{
			pPlayer->m_bIsRight = true;
			pPlayer->m_vPos.x += 20;
		}
		pPlayer->Attack();
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		m_fDuration = 0.3f;
		m_fCurTime = 0.f;
		m_bOnceFunc = true;
		m_fOnceFuncTime = 0.3f;
		m_fOnceFuncCurTime = 0.f;
		pPlayer->GetAnimator()->Play(L"Hunter_AttackReady", true);
		break;
	}
	}
}

void CPlayerStateAttack::Exit(CObject* _pObj)
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
