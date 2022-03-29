#pragma once
#include "CUI.h"
class CUIPanel :
    public CUI
{
private:
    Vec2 m_vDragStart;
public:
    CUIPanel(OBJ_TYPE _eType);
    CUIPanel(const CUIPanel& _origin);
    virtual ~CUIPanel();

    virtual void Render();
    virtual CUIPanel* Clone();

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();

};

