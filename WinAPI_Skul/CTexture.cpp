#include "pch.h"
#include "CTexture.h"
#include "CGameObject.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBMP = 0;
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 비트맵 형태로 가져오며 사이즈는 기본값으로 가져온다(이미지만큼)
	m_hBMP = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
			  0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBMP); // 제대로 불러오지 못한 경우 오류 발생

	// 비트맵과 연결할 DC
	m_hDC = CreateCompatibleDC(SINGLE(CCore)->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPervBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hPervBit);

	// 가로 세로 길이
	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);

}

void CTexture::Create(UINT _width, UINT _height)
{
	HDC mainDC = SINGLE(CCore)->GetMainDC();
	m_hBMP = CreateCompatibleBitmap(mainDC, _width, _height);
	m_hDC = CreateCompatibleDC(mainDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hOldBmp);

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}
