#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI*	m_pFocusedUI;

public:
	void	Update();
	void	SetFocusedUI(CUI* _pUI); // 요청한 UI를 FocusedUI로 지정하는 함수
	CUI*	GetFocusedUI();					// 포커스 UI를 구하는 함수
private:
	CUI*	GetTargetUI(CUI* _pParentUI);	// 타겟 UI를 구하는 함수
	
};

