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
	// �ҷ��� ���ҽ����� �޸� ���� ��Ų��.
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
	// �ؽ��ĸ� ���� Ž���غ��� �ִٸ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;


	// �ҷ��� �ؽ��İ� ���ٸ� �ҷ����� ������ �����ϰ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.
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

	// �ؽ��ĸ� ã�� ���ߴٸ� ������Ʈ ��ȯ
	if (iter == m_mapTex.end()) 
		return nullptr;

	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{
	// ���带 ���� Ž���غ��� �ִٸ� �ش� ���带 ��ȯ�Ѵ�.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound) return pSound;

	// �ҷ��� ���尡 ���ٸ� �ҷ����� ������ �����ϰ� �ش� ���带 ��ȯ�Ѵ�.
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

	// ���带 ã�� ���ߴٸ� ������Ʈ ��ȯ
	if (iter == m_mapSound.end()) 
		return nullptr;

	return (CSound*)iter->second;
}
