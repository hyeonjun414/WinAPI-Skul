#include "pch.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSound.h"

CResourceManager::CResourceManager():
	m_mapTex{},
	m_mapSound{}
{}

CResourceManager::~CResourceManager()
{
	// 불러온 리소스들을 메모리 해제 시킨다.
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;

	pTex = new CTexture();
	pTex->Create(_width, _height);
	pTex->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 텍스쳐를 먼저 탐색해보고 있다면 해당 텍스쳐를 반환한다.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;


	// 불러온 텍스쳐가 없다면 불러오는 과정을 진행하고 해당 텍스쳐를 반환한다.
	wstring strFilePath = SINGLE(CPathManager)->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);

	// 텍스쳐를 찾지 못했다면 널포인트 반환
	if (iter == m_mapTex.end()) 
		return nullptr;

	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{
	// 사운드를 먼저 탐색해보고 있다면 해당 사운드를 반환한다.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound) return pSound;

	// 불러온 사운드가 없다면 불러오는 과정을 진행하고 해당 사운드를 반환한다.
	wstring strFilePath = SINGLE(CPathManager)->GetContextRelativePath();
	strFilePath += _strRelativePath;

	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	// 사운드를 찾지 못했다면 널포인트 반환
	if (iter == m_mapSound.end()) 
		return nullptr;

	return (CSound*)iter->second;
}
