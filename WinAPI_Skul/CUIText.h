#pragma once
#include "CUI.h"
class CUIText :
    public CUI
{
protected:
    wstring    m_strText;

public:
    CUIText(OBJ_TYPE _eType);
    virtual ~CUIText();

    virtual void Render();

    void            SetText(const wstring& _text)       { m_strText = _text; }
    const wstring&  GetText()                           { return m_strText; }
};

