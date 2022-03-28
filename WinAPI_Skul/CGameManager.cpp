#include "pch.h"
#include "CGameManager.h"
#include "CUIText.h"
#include "CUIImage.h"
#include "CEffect.h"
#include "CTextObj.h"
#include "CPlayer.h"
#include "CVfx.h"
#include "CLittleBorn.h"
#include "CHunter.h"
#include "CMenuUI.h"

CGameManager::CGameManager():
	m_pPlayer(nullptr)
{}
CGameManager::~CGameManager() 
{

}

void CGameManager::Init()
{
}

void CGameManager::Update()
{

	if (KEYTAP(KEY::ESC))
	{
		ActiveMenu();
	}

	if (nullptr != m_pTimer)
	{
		int h, m, s;
		float fPlayTime = SINGLE(CTimeManager)->GetPlayTime();
		WCHAR strPlayTime[13];
		h = (int)(fPlayTime / 3600.f);
		m = (int)(fPlayTime / 60.f);
		s = (int)fPlayTime % 60;
		swprintf_s(strPlayTime, L"%02d : %02d : %02d", h, m, s);
		m_pTimer->SetText(strPlayTime);
	}
	if (nullptr != m_pRemainEnemy)
	{
		m_pRemainEnemy->SetText(to_wstring(m_iRemainEnemyCount));
	}


}

CPlayer* CGameManager::GetCurSkul()
{
	if (nullptr != m_pPlayer)
	{
		if (nullptr != m_pPlayer2)
		{
			m_pSubSkillFrame->SetActive(true);
			m_pSubSkulFrame->SetActive(true);
			m_pPlayer2->Exit();
			CREATEOBJECT(m_pPlayer2);
		}
		m_pPlayer->Enter();
		CREATEOBJECT(m_pPlayer);
		return m_pPlayer;

	}

	CPlayer* obj = new CLittleBorn(OBJ_TYPE::PLAYER);
	obj->Init();
	obj->SetName(L"Player");
	CREATEOBJECT(obj);
	m_pPlayer = obj;
	return obj;
}

void CGameManager::SwitchSkul()
{
	if (nullptr == m_pPlayer2) return;

	m_pPlayer->Exit();
	CPlayer* pPlayer2 = m_pPlayer2;
	m_pPlayer2 = m_pPlayer;
	m_pPlayer = pPlayer2;
	m_pPlayer->GetPlayerInfo() = m_pPlayer2->GetPlayerInfo();
	m_pPlayer->Enter();
	m_pPlayer->SetPos(m_pPlayer2->GetPos() + Vec2(0, -3));
	m_pPlayer->SetObjDir(m_pPlayer2->GetObjDir());
	SINGLE(CCameraManager)->SetTarget(m_pPlayer);
}

void CGameManager::AddSkul(SKUL_TYPE _eSkulType)
{
	 //두번째 스컬이 없다면 현재 스컬을 두번쨰 스컬로보내고
	 //현재 스컬을 새로운 스컬로 대체한다.
	if (nullptr == m_pPlayer2)
	{
		CPlayer* pNew = nullptr;
		switch (_eSkulType)
		{
		case SKUL_TYPE::Little_Born:
			pNew = new CLittleBorn(OBJ_TYPE::PLAYER);
			break;
		case SKUL_TYPE::Hunter:
			pNew = new CHunter(OBJ_TYPE::PLAYER);
			break;
		}
		pNew->Init();
		pNew->Exit();
		m_pPlayer2 = pNew;
		CREATEOBJECT(pNew);
		m_pSubSkillFrame->SetActive(true);
		m_pSubSkulFrame->SetActive(true);


		SwitchSkul();
	}
	// 두번째 스컬이 있다면 새로운 스컬을 만들고 첫번째 스컬의 위치정보를 옮긴뒤
	// 첫번째 스컬을 삭제하고 첫번째스컬을 생성한다.
	else
	{
		CPlayer* pNew = nullptr;
		switch (_eSkulType)
		{
		case SKUL_TYPE::Little_Born:
			pNew = new CLittleBorn(OBJ_TYPE::PLAYER);
			break;
		case SKUL_TYPE::Hunter:
			pNew = new CHunter(OBJ_TYPE::PLAYER);
			break;
		}
		pNew->Init();
		pNew->SetPos(m_pPlayer->GetPos());
		pNew->GetPlayerInfo() = m_pPlayer->GetPlayerInfo();
		DELETEOBJECT(m_pPlayer);
		m_pPlayer->Exit();
		m_pPlayer = pNew;
		CREATEOBJECT(m_pPlayer);
		m_pPlayer->Enter();
		SINGLE(CCameraManager)->SetTarget(m_pPlayer);
	}

}

void CGameManager::EraseHeadObj()
{
	CPlayer* pPlayer = (CPlayer*)m_pPlayer;
	pPlayer->m_pHead = nullptr;
}

void CGameManager::CreateVfx(const wstring& _strKey, const wstring& _strPath, Vec2 _vPos, float _fDuration, float _fInterval, bool _bDir, float _size)
{
	CVfx* pEft = new CVfx(_strKey, _strPath, _fDuration, _fInterval,_bDir);
	pEft->SetPos(_vPos);
	pEft->SetSizeRate(_size);
	CREATEOBJECT(pEft);
}

void CGameManager::DamageText(const wstring& _strDamage, Vec2 _vPos, Color _color)
{
	CTextObj* pDamage = new CTextObj(OBJ_TYPE::HUD, _strDamage, TEXT_EFFECT::BOUNCE, _color);
	pDamage->SetPos(_vPos);
	CREATEOBJECT(pDamage);

}

int CGameManager::RandomInt(int _value, float _volume)
{
	// 10 * 2 = 20 10 - 10
	//int value = _value * _volume;
	// volume의 두배만큼 값을 받은 다음 +-volume 처리를 위해 값을 빼준다.
	// ex) 10 -> 20 -> +- 10;
	int randValue = rand()%(int)(_value * _volume * 2.f) - (_value * _volume);
	// randValue = rand()%4 - 2;
	int result = _value + randValue;
	return result;
}

void CGameManager::ActiveMenu()
{
	m_bIsPlay = !m_bIsPlay;
	m_pMenuUI->SetActive(!m_bIsPlay);
	if (m_pMenuUI->IsActive())
		SINGLE(CUIManager)->SetFocusedUI(m_pMenuUI);
	else
		SINGLE(CUIManager)->SetFocusedUI(nullptr);
}

void CGameManager::GameExit()
{
	PostQuitMessage(0);
}

void CGameManager::Reset()
{
	m_pPlayer = nullptr;
	m_pPlayer2 = nullptr;

	m_pTimer = nullptr;
	m_pRemainEnemy = nullptr;
	m_pCurHealth = nullptr;
	m_pCurHealthText = nullptr;
	
	m_pPortrait = nullptr;
	m_pSkillA = nullptr;
	m_pSkillB = nullptr;
	m_pSubSkillA = nullptr;
	m_pSubSkillB = nullptr;
	m_pSubSkul = nullptr;
	
	m_pSubSkillFrame = nullptr;
	m_pSubSkulFrame = nullptr;
	
	m_pBossStatus = nullptr;
	
	m_pMenuUI = nullptr;
}


