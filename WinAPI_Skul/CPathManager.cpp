#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager():
	m_strContentPath{}
{}

CPathManager::~CPathManager()
{}

void CPathManager::Init()
{
	GetCurrentDirectory(255, m_strContentPath); // ���� ��θ� �޾ƿ´�.

	int iLen = (int)wcslen(m_strContentPath);

	// �ʿ� ��� �߰�
	wcscat_s(m_strContentPath, 255, L"\\bin\\");
}

const wchar_t* CPathManager::GetContextRelativePath()
{
	return L"..\\Release\\bin\\";
}
