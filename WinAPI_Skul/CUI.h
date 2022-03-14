#pragma once
#include "CGameObject.h"
class CUI :
    public CGameObject
{
    friend class CUIManager;
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;

    Vec2            m_vFinalPos;        // 상대적으로 그려질 위치
    
    bool            m_bCameraAffected;  // 카메라의 영향의 받는가
    bool            m_bMouseOn;         // UI가 이전 프레임에 마우스가 올려져 있었다.
    bool            m_bLbtnDown;        // UI가 이전 프레임에 눌려져 있었다.
public:
    CUI(OBJ_TYPE _eType);
    CUI(const CUI& _origin);
    virtual ~CUI();
    virtual CUI* Clone();

    virtual void    Init();
    virtual void    Update();
    virtual void    FinalUpdate();
    virtual void    Render(HDC _hDC);

    void            UpdateChild();
    void            FinalUpdateChild();
    void            RenderChild(HDC _hDC);

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();
    virtual void    MouseLbtnClick();

    void            SetCameraAffected(bool _bAffect);

    Vec2            GetFinalPos()           { return m_vFinalPos; }
    CUI*            GetParent()             { return m_pParentUI; }
    const vector<CUI*>& GetChild()          { return m_vecChildUI; }
    bool            GetCameraAffected()     { return m_bCameraAffected; }
    bool            IsMouseOn()             { return m_bMouseOn; }
    bool            IsLbtnDown()            { return m_bLbtnDown; }

    void            AddChild(CUI* _pUI);

private:
    void            MouseOnCheck();
};

