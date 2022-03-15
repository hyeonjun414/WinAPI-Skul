#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
    
private:
    HDC         m_hDC;              
    HBITMAP     m_hBMP;
    BITMAP      m_bmpInfo;

    friend CResourceManager;
    CTexture();
    virtual ~CTexture();

public:
    void        Load(const wstring& _strFilePath);
    void        Create(UINT _width, UINT _height);

    UINT        Width() { return m_bmpInfo.bmWidth; }
    UINT        Height() { return m_bmpInfo.bmHeight; }

    HDC         GetDC() { return m_hDC; }
    HBITMAP     GetBitmap() { return m_hBMP; }
};

