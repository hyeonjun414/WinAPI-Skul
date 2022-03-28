#pragma once
#include "CUI.h"
class CUIImage :
    public CUI
{
protected:
    CD2DImage* m_pImg;
    Vec2       m_vScaleRate;
    Vec2       m_vOriginScaleRate;

public:
    CUIImage(OBJ_TYPE _eType);
    CUIImage(OBJ_TYPE _eType, const wstring& _strKey, const wstring& _strPath, Vec2 _sizeRate = Vec2(1.f,1.f));
    virtual ~CUIImage();

    virtual void    Render();

    void            SetScaleRate(Vec2 _vScaleRate)      { m_vScaleRate = _vScaleRate; }
    Vec2           GetScaleRate()                       { return m_vScaleRate; }
    Vec2            GetOriginSize()                     { return m_vOriginScaleRate; }
    CD2DImage*      GetImage()                          { return m_pImg; }
    void            SetImage(const wstring& _strKey, const wstring& _strPath);

};

