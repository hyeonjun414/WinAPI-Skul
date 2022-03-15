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
		// lParam : 오브젝트 주소
		// wParam : 오브젝트 그룹
		CObject* pObj = (CObject*)_event.lParam;
		SINGLE(CSceneManager)->GetCurScene()->AddObject(pObj);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// 오브젝트를 Dead상태로 변경하고
		// 삭제 예정 오브젝트들을 모아둔다.
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
	// 삭제 예정 오브젝트를 삭제한다.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// 저장된 이벤트를 순서대로 처리한다.
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
