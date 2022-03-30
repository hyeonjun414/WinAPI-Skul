#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI*	m_pFocusedUI;

public:
	void	Update();
	void	SetFocusedUI(CUI* _pUI); // ��û�� UI�� FocusedUI�� �����ϴ� �Լ�
	CUI*	GetFocusedUI();					// ��Ŀ�� UI�� ���ϴ� �Լ�
private:
	CUI*	GetTargetUI(CUI* _pParentUI);	// Ÿ�� UI�� ���ϴ� �Լ�
	
};

