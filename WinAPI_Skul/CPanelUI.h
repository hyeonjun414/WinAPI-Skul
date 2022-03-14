#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2 m_vDragStart;
public:
    CPanelUI(OBJ_TYPE _eType);
    CPanelUI(const CPanelUI& _origin);
    virtual ~CPanelUI();

    virtual CPanelUI* Clone();

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();

};

