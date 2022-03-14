#include "pch.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager():
	m_pFocusedUI(nullptr)
{}
CUIManager::~CUIManager()
{}

void CUIManager::Update()
{
	// UI매니저가 계속해서 포커싱된 UI를 가지고있도록 만들어준다.
	m_pFocusedUI = GetFocusedUI();
	if (nullptr == m_pFocusedUI) return;

	// 이미 GetFocusedUI에서 모든 UI를 순회하면 포커싱된 UI를 구했으므로
	// pUI를 m_pFocusedUI로 받아와 타겟으로 실행하면 된다.
	CUI* pUI = GetTargetUI(m_pFocusedUI);

	if (nullptr != pUI)
	{
		pUI->MouseOn();
		if (KEYCHECK(KEY::LBTN) == KEY_STATE::HOLD)
		{
			pUI->MouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (KEYCHECK(KEY::LBTN) == KEY_STATE::AWAY)
		{
			pUI->MouseLbtnUp();
			if (pUI->m_bLbtnDown) // 눌리고 있는 상황
			{
				pUI->MouseLbtnClick();
			}
			pUI->m_bLbtnDown = false;
		}
	}
}

void CUIManager::SetFocusedUI(CUI* _pUI)
{
	// 외부 클래스의 요청에 의한 FocusUI 변경

	// 이미 포커싱된 UI라면 무시
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CGameObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (_pUI == *iter)
		{
			m_pFocusedUI = _pUI;
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}
}

CUI* CUIManager::GetTargetUI(CUI* _pParentUI)
{
	// 클릭하는 UI의 최하단 UI를 부르도록 하는 함수 -> 순회하여 탐색해야함.
	list<CUI*>		queue;
	vector<CUI*>	vecNoneTarget;


	CUI* pTargerUI = nullptr;
	queue.push_back(_pParentUI); // 부모를 우선 탐색

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargerUI)
			{
				vecNoneTarget.push_back(pTargerUI);
			}
			pTargerUI = pUI;
		}
		else
		{
			// 애초에 마우스가 안올라갔던 UI도 논타겟으로 설정
			vecNoneTarget.push_back(pUI);
		}
		const vector<CUI*> vecChild = pUI->GetChild();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 논타겟 UI는  마우스가 안올라간것으로 설정
	if (KEYCHECK(KEY::LBTN) == KEY_STATE::AWAY)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargerUI;
}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();
	CUI* pFocusedUI = m_pFocusedUI; // 포커싱 되어있던 UI를 넣어줌.

	// 마우스가 눌린상태가 아니라면 이전에 포커싱한 UI를 반환한다.
	if (!(KEYCHECK(KEY::LBTN) == KEY_STATE::HOLD))
	{
		return m_pFocusedUI;
	}

	vector<CGameObject*>::iterator targetiter	=	vecUI.end();	
	vector<CGameObject*>::iterator iter			=	vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		// 클릭이 된 상태이면서 해당 UI에 마우스가 올라가 있어야 한다.
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter; // 해당 UI를 target으로 지정
		}
	}

	// 포커싱된 UI가 없다면
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	// 포커싱된 UI가 있다면
	pFocusedUI = (CUI*)*targetiter;

	// 선택한 UI가 가장 뒤에 배치되도록 만든다.
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
