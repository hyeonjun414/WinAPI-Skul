#pragma once
#include "CUIButton.h"
class CUITileBtn :
    public CUIButton
{
private:
	int m_iIdx;

public:
	CUITileBtn(OBJ_TYPE _eType);
	virtual ~CUITileBtn();

	virtual void Render();

	int GetIdx() { return m_iIdx; }
	void SetIdx(int _idx) { m_iIdx = _idx; }
};

