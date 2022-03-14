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
	// ��Ʈ�� ���·� �������� ������� �⺻������ �����´�(�̹�����ŭ)
	m_hBMP = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
			  0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBMP); // ����� �ҷ����� ���� ��� ���� �߻�

	// ��Ʈ�ʰ� ������ DC
	m_hDC = CreateCompatibleDC(SINGLE(CCore)->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPervBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hPervBit);

	// ���� ���� ����
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
