#include "pch.h"
#include "Stateheader.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayerState* CPlayerStateIdle::HandleInput(CObject* _pObj)
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


	//스컬 타입마다 달라야하는 기능은 아래에 같아도 되는 작업은 위에
	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (KEYHOLD(KEY::LEFT))
		{
			pPlayer->SetObjDir(false);
			return new CPlayerStateMove();
		}
		if (KEYHOLD(KEY::RIGHT))
		{
			pPlayer->SetObjDir(true);
			return new CPlayerStateMove();
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
			pPlayer->m_bCanDash = false;
			return new CPlayerStateDash();
		}
		if (KEYTAP(KEY::C))
		{
			if (KEYHOLD(KEY::DOWN))
			{
				pPlayer->m_vPos.y += 3;
				pPlayer->m_bIsGround = false;
				return new CPlayerStateFall();
			}
			return new CPlayerStateJump();
		}
		if (KEYTAP(KEY::X))
		{
			return new CPlayerStateAttack();
		}
		if (!pPlayer->IsGround())
			return new CPlayerStateFall();


		break;
	}
	case SKUL_TYPE::Hunter:
	{
		if (KEYHOLD(KEY::LEFT))
		{
			pPlayer->SetObjDir(false);
			return new CPlayerStateMove();
		}
		if (KEYHOLD(KEY::RIGHT))
		{
			pPlayer->SetObjDir(true);
			return new CPlayerStateMove();
		}
		if (KEYTAP(KEY::A))
		{
			return new CPlayerStateSkillA();
		}
		if (KEYTAP(KEY::S))
		{
			return new CPlayerStateSkillB();
		}
		if (KEYTAP(KEY::Z) && pPlayer->m_bCanDash)
		{
			pPlayer->m_bCanDash = false;
			return new CPlayerStateDash();
		}
		if (KEYTAP(KEY::C))
		{
			if (KEYHOLD(KEY::DOWN))
			{
				pPlayer->m_vPos.y += 3;
				pPlayer->m_bIsGround = false;
				return new CPlayerStateFall();
			}
			return new CPlayerStateJump();
		}
		if (KEYTAP(KEY::X))
		{
			return new CPlayerStateAttack();
		}
		if (!pPlayer->IsGround())
			return new CPlayerStateFall();


		break;
	}
	}
    return nullptr;
}

void CPlayerStateIdle::Update(CObject* _pObj)
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

void CPlayerStateIdle::Enter(CObject* _pObj)
{
	CPlayer* pPlayer = (CPlayer*)_pObj;
	switch (pPlayer->m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
	{
		if (pPlayer->m_bCanSkill)
			pPlayer->GetAnimator()->Play(L"LittleBorn_Idle", true);
		else
			pPlayer->GetAnimator()->Play(L"LittleBorn_Idle_Headless", true);
		pPlayer->m_strCurState = L"Idle";
		break;
	}
	case SKUL_TYPE::Hunter:
	{
		pPlayer->GetAnimator()->Play(L"Hunter_Idle", true);
		break;
	}
	}
}

void CPlayerStateIdle::Exit(CObject* _pObj)
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
