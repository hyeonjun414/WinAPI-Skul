#include "pch.h"
#include "CSoundManager.h"
#include "CSound.h"

CSoundManager::CSoundManager():
	m_pSystem(nullptr)
{

}
CSoundManager::~CSoundManager()
{
	m_pSystem->close();
	m_pSystem->release();
}

void CSoundManager::Init()
{
	FMOD_RESULT result;

	System_Create(&m_pSystem);

	result = m_pSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	assert(!result);

}

void CSoundManager::Update()
{
	// 프레임마다 꼭 시스템을 업데이트해야한다.
	m_pSystem->update();
}

void CSoundManager::AddSound(wstring _keyName, wstring _filePath, bool _loop)
{
	CSound* pSound = SINGLE(CResourceManager)->LoadSound(_keyName, _filePath);
	pSound->SetLoop(_loop);
	m_mapSound.insert(make_pair(_keyName, pSound));
}

void CSoundManager::Play(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		return;
	iter->second->Play();

}


void CSoundManager::Stop(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		return;

	iter->second->Stop();
}

void CSoundManager::Pause(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		return;

	iter->second->Pause();
}

void CSoundManager::Resume(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		return;

	iter->second->Resume();
}

bool CSoundManager::IsPlaySound(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		assert(nullptr);

	return iter->second->IsPlay();
}

bool CSoundManager::IsPauseSound(wstring _keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_keyName);
	if (iter == m_mapSound.end()) 
		assert(nullptr);

	return iter->second->IsPause();
}
