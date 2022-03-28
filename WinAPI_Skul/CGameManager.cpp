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
	{
		if (nullptr != m_pPlayer2)
		{
			m_pSubSkillFrame->SetActive(true);
			m_pSubSkulFrame->SetActive(true);
			m_pPlayer2->Exit();
		}
		m_pPlayer->Enter();
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
	 //�ι�° ������ ���ٸ� ���� ������ �ι��� ���÷κ�����
	 //���� ������ ���ο� ���÷� ��ü�Ѵ�.
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
	// �ι�° ������ �ִٸ� ���ο� ������ ����� ù��° ������ ��ġ������ �ű��
	// ù��° ������ �����ϰ� ù��°������ �����Ѵ�.
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
	// volume�� �ι踸ŭ ���� ���� ���� +-volume ó���� ���� ���� ���ش�.
	// ex) 10 -> 20 -> +- 10;
	int randValue = rand()%(int)(_value * _volume * 2.f) - (_value * _volume);
	// randValue = rand()%4 - 2;
	int result = _value + randValue;
	return result;
}


