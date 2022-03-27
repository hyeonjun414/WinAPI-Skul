#include "pch.h"
#include "CGameManager.h"
#include "CUIText.h"
#include "CUIImage.h"
#include "CEffect.h"
#include "CTextObj.h"
#include "CPlayer.h"
#include "CVfx.h"
#include "CLittleBorn.h"

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
		return m_pPlayer;

	CPlayer* obj = new CLittleBorn(OBJ_TYPE::PLAYER);
	obj->Init();
	obj->SetName(L"Player");
	CREATEOBJECT(obj);
	return obj;
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
	// volume�� �ι踸ŭ ���� ���� ���� +-volume ó���� ���� ���� ���ش�.
	// ex) 10 -> 20 -> +- 10;
	int randValue = rand()%(int)(_value * _volume * 2.f) - (_value * _volume);
	// randValue = rand()%4 - 2;
	int result = _value + randValue;
	return result;
}


