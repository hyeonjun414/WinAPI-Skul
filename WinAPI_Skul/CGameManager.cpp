#include "pch.h"
#include "CGameManager.h"
#include "CUIText.h"

CGameManager::CGameManager():
	m_pPlayer(nullptr)
{}
CGameManager::~CGameManager() {}

void CGameManager::Init()
{
}

void CGameManager::Update()
{
	if (nullptr != m_pPlayer)
	{

	}

	if (nullptr != m_pTimer)
	{
		int h, m, s;
		float fPlayTime = SINGLE(CTimeManager)->GetPlayTime();
		WCHAR strPlayTime[13];
		h = fPlayTime / 3600;
		m = fPlayTime / 60;
		s = (int)fPlayTime % 60;
		swprintf_s(strPlayTime, L"%02d : %02d : %02d", h, m, s);
		m_pTimer->SetText(strPlayTime);
	}
	if (nullptr != m_pRemainEnemy)
	{
		m_pRemainEnemy->SetText(to_wstring(m_iRemainEnemyCount));
	}

}

