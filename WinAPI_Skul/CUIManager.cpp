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
	// UI�Ŵ����� ����ؼ� ��Ŀ�̵� UI�� �������ֵ��� ������ش�.
	m_pFocusedUI = GetFocusedUI();
	if (nullptr == m_pFocusedUI) return;

	// �̹� GetFocusedUI���� ��� UI�� ��ȸ�ϸ� ��Ŀ�̵� UI�� �������Ƿ�
	// pUI�� m_pFocusedUI�� �޾ƿ� Ÿ������ �����ϸ� �ȴ�.
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
			if (pUI->m_bLbtnDown) // ������ �ִ� ��Ȳ
			{
				pUI->MouseLbtnClick();
			}
			pUI->m_bLbtnDown = false;
		}
	}
}

void CUIManager::SetFocusedUI(CUI* _pUI)
{
	// �ܺ� Ŭ������ ��û�� ���� FocusUI ����

	// �̹� ��Ŀ�̵� UI��� ����
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
	// Ŭ���ϴ� UI�� ���ϴ� UI�� �θ����� �ϴ� �Լ� -> ��ȸ�Ͽ� Ž���ؾ���.
	list<CUI*>		queue;
	vector<CUI*>	vecNoneTarget;


	CUI* pTargerUI = nullptr;
	queue.push_back(_pParentUI); // �θ� �켱 Ž��

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
			// ���ʿ� ���콺�� �ȿö󰬴� UI�� ��Ÿ������ ����
			vecNoneTarget.push_back(pUI);
		}
		const vector<CUI*> vecChild = pUI->GetChild();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// ��Ÿ�� UI��  ���콺�� �ȿö󰣰����� ����
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
	CUI* pFocusedUI = m_pFocusedUI; // ��Ŀ�� �Ǿ��ִ� UI�� �־���.

	// ���콺�� �������°� �ƴ϶�� ������ ��Ŀ���� UI�� ��ȯ�Ѵ�.
	if (!(KEYCHECK(KEY::LBTN) == KEY_STATE::HOLD))
	{
		return m_pFocusedUI;
	}

	vector<CGameObject*>::iterator targetiter	=	vecUI.end();	
	vector<CGameObject*>::iterator iter			=	vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		// Ŭ���� �� �����̸鼭 �ش� UI�� ���콺�� �ö� �־�� �Ѵ�.
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter; // �ش� UI�� target���� ����
		}
	}

	// ��Ŀ�̵� UI�� ���ٸ�
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	// ��Ŀ�̵� UI�� �ִٸ�
	pFocusedUI = (CUI*)*targetiter;

	// ������ UI�� ���� �ڿ� ��ġ�ǵ��� �����.
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
