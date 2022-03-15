#include "pch.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CObject.h"

CEventManager::CEventManager(){}
CEventManager::~CEventManager(){}

void CEventManager::Excute(const tEvent& _event)
{
	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : ������Ʈ �ּ�
		// wParam : ������Ʈ �׷�
		CObject* pObj = (CObject*)_event.lParam;
		SINGLE(CSceneManager)->GetCurScene()->AddObject(pObj);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// ������Ʈ�� Dead���·� �����ϰ�
		// ���� ���� ������Ʈ���� ��Ƶд�.
		CObject* pObj = (CObject*)_event.lParam;
		if (!pObj->GetActive()) break;
		pObj->SetActive(false);
		m_vecDead.push_back(pObj);
		break;
	}
	case EVENT_TYPE::SCENE_CHANGE:
	{
		SINGLE(CSceneManager)->ChangeScene((SCENE_TYPE)_event.lParam);
		SINGLE(CUIManager)->SetFocusedUI(nullptr);
		break;
	}
	}
}

void CEventManager::Update()
{
	// ���� ���� ������Ʈ�� �����Ѵ�.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ����� �̺�Ʈ�� ������� ó���Ѵ�.
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::EventCreateObject(CObject* _pObj)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::CREATE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	AddEvent(even);
}

void CEventManager::EventDeleteObject(CObject* _pObj)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::DELETE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	AddEvent(even);
}

void CEventManager::EventChangeScene(SCENE_TYPE _eSceneType)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::SCENE_CHANGE;
	even.lParam = (DWORD_PTR)_eSceneType;

	AddEvent(even);
}
