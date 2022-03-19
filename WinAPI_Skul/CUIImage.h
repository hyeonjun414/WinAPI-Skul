#pragma once
#include "CUI.h"
class CUIImage :
    public CUI
{
protected:
    CD2DImage* m_pImg;
    Vec2       m_vScaleRate;

public:
    CUIImage(OBJ_TYPE _eType, const wstring& _strKey, const wstring& _strPath);
    ~CUIImage();

    virtual void    Render();

    void            SetScaleRate(Vec2 _vScaleRate)     { m_vScaleRate = _vScaleRate; }
    Vec2           GetScaleRate()                      { return m_vScaleRate; }
    CD2DImage*      GetImage()                          { return m_pImg; }
};

