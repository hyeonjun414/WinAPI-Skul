#pragma once
#include "CUI.h"

class CD2DImage;

class CUICursor :
    public CUI
{
private:
    CD2DImage* m_pImg;

public:
    CUICursor(OBJ_TYPE _eType);
    CUICursor(const CUICursor& _origin);
    virtual ~CUICursor();

    virtual void Update();
    virtual void Render();
};

