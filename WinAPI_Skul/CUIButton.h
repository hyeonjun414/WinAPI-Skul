#pragma once
#include "CUI.h"

// 함수포인터 형변환
typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CUIButton :
    public CUI
{
private:
    BTN_FUNC    m_pFunc; // 기능을 부여할 함수 포인터
    DWORD_PTR   m_pParam1;
    DWORD_PTR   m_pParam2;

protected:
    CD2DImage*  m_pImg;
    wstring     m_strText;
    Color       m_eOnColor;
    Color       m_eOffColor;
    float       m_fFontSize;
public:
    CUIButton(OBJ_TYPE _eType);
    CUIButton(const CUIButton& _origin);
    ~CUIButton();

    virtual CUIButton* Clone();

    virtual void    Update();
    virtual void    FinalUpdate();
    virtual void    Render();

    virtual void    MouseOn();
    virtual void    MouseLbtnDown();
    virtual void    MouseLbtnUp();
    virtual void    MouseLbtnClick();

    void            SetFontSize(float _fSize) { m_fFontSize = _fSize; }
    float           GetFontSize() { return m_fFontSize; }
    void            SetOnColor(Color _eColor) { m_eOnColor = _eColor; }
    void            SetOffColor(Color _eColor) { m_eOffColor = _eColor; }
    void            SetImage(CD2DImage* _img);
    void            SetText(const wstring& str, float _fontSize = 14.f);
    void            PositionSet();
    void            SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2);

};

