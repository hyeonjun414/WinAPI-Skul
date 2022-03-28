#pragma once
#include "CUI.h"
class CUIText :
    public CUI
{
protected:
    wstring    m_strText;
    float      m_fFontSize;
    Color      m_eFontColor;

public:
    CUIText(OBJ_TYPE _eType);
    virtual ~CUIText();

    virtual void Render();

    void            SetText(const wstring& _text)       { m_strText = _text; }
    const wstring&  GetText()                           { return m_strText; }

    void            SetFontColor(Color _eColor)         { m_eFontColor = _eColor; }
    void            SetFontSize(float _fSize)           { m_fFontSize = _fSize; }
    float           GetFontSize()                       { return m_fFontSize; }

    void            PositionSet();

};

