#pragma once
#include "CUI.h"
class CUIText :
    public CUI
{
protected:
    wstring    m_strText;
    float      m_fFontSize;

public:
    CUIText(OBJ_TYPE _eType);
    virtual ~CUIText();

    virtual void Render();

    void            SetText(const wstring& _text)       { m_strText = _text; }
    const wstring&  GetText()                           { return m_strText; }

    void            SetFontSize(float _fSize) { m_fFontSize = _fSize; }
    float           SetFontSize() { return m_fFontSize; }
};

