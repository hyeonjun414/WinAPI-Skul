#pragma once
#include "CUI.h"

// �Լ������� ����ȯ
typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CButtonUI :
    public CUI
{
private:
    BTN_FUNC    m_pFunc; // ����� �ο��� �Լ� ������
    DWORD_PTR   m_pParam1;
    DWORD_PTR   m_pParam2;
public:
    CButtonUI(OBJ_TYPE _eType);
    CButtonUI(const CButtonUI& _origin);
    ~CButtonUI();

    virtual CButtonUI* Clone();

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();
    virtual void    MouseLbtnClick();

    void SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2);

};

