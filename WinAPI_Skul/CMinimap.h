#pragma once
#include "CUI.h"
class CMinimap :
    public CUI
{
public:
    CMinimap();
    virtual ~CMinimap();

    virtual void Init();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render();
};