#pragma once
#include "CUI.h"

// �Լ������� ����ȯ
typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CUIButton :
    public CUI
{
private:
    BTN_FUNC    m_pFunc; // ����� �ο��� �Լ� ������
    DWORD_PTR   m_pParam1;
    DWORD_PTR   m_pParam2;

protected:
    CD2DImage* m_pImg;
    wstring m_strText;
public:
    CUIButton(OBJ_TYPE _eType);
    CUIButton(const CUIButton& _origin);
    ~CUIButton();

    virtual CUIButton* Clone();

    virtual void Render();

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();
    virtual void    MouseLbtnClick();

    void SetImage(CD2DImage* _img);
    void SetText(const wstring& str);

    void SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2);

};

