#pragma once
#include "CUI.h"
class CMenuUI :
    public CUI
{
public:
    CMenuUI();
    virtual ~CMenuUI();

    virtual void Init();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render();

};

