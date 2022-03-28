#pragma once
#include "CUI.h"
class CStatusHUD :
    public CUI
{
public:
    CStatusHUD();
    virtual ~CStatusHUD();
    
    virtual void Init();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render();
};

