#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
    
private:
    HDC         m_hDC;              
    HBITMAP     m_hBMP;
    BITMAP      m_bmpInfo;


    // 리소스 매니저만 해당 객체를 생성할 수 있게 private로 만든 후
    // friend 클래스로 CResourceManager를 지정해준다.

    friend CResourceManager;
    CTexture();
    virtual ~CTexture();

public:
    void        Load(const wstring& _strFilePath);
    void        Create(UINT _width, UINT _height);
    //void        Render(HDC _hDC);

    UINT        Width() { return m_bmpInfo.bmWidth; }
    UINT        Height() { return m_bmpInfo.bmHeight; }

    HDC         GetDC() { return m_hDC; }
    HBITMAP     GetBitmap() { return m_hBMP; }
};

