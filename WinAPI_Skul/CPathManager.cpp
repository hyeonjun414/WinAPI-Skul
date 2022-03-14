#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager():
	m_strContentPath{}
{}

CPathManager::~CPathManager()
{}

void CPathManager::Init()
{
	GetCurrentDirectory(255, m_strContentPath); // 현재 경로를 받아온다.

	int iLen = (int)wcslen(m_strContentPath);

	// 필요 경로 추가
	wcscat_s(m_strContentPath, 255, L"\\bin\\");
}

const wchar_t* CPathManager::GetContextRelativePath()
{
	return L"..\\Release\\bin\\";
}
