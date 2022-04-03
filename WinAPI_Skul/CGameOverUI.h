#pragma once
#include "CUI.h"
class CGameOverUI :
    public CUI
{
public:
    CGameOverUI();
    virtual ~CGameOverUI();

    virtual void Init();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render();
};

