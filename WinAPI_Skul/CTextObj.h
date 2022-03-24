#pragma once
#include "CObject.h"
class CTextObj :
    public CObject
{
protected:
    wstring     m_strText;
    Vec2        m_vVelocity;
    float       m_fCurTime;
    float       m_fDuration;
    Color       m_eColor;

public:
    CTextObj(OBJ_TYPE _eType, const wstring& _strText, TEXT_EFFECT _eEffect, Color _color = Color::WHITE);
    virtual ~CTextObj();

    virtual void Update();
    virtual void Render();

    void                SetText(const wstring& _text)   { m_strText = _text; }
    const wstring&      GetText()                       { return m_strText; }
};

