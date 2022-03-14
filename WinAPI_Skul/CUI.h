#pragma once
#include "CGameObject.h"
class CUI :
    public CGameObject
{
    friend class CUIManager;
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;

    Vec2            m_vFinalPos;        // ��������� �׷��� ��ġ
    
    bool            m_bCameraAffected;  // ī�޶��� ������ �޴°�
    bool            m_bMouseOn;         // UI�� ���� �����ӿ� ���콺�� �÷��� �־���.
    bool            m_bLbtnDown;        // UI�� ���� �����ӿ� ������ �־���.
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

