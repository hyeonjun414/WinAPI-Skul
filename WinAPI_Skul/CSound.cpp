#include "pch.h"
#include "CSound.h"

CSound::CSound():
	m_pSound(nullptr),
	m_pChannel(nullptr)
{
}

CSound::~CSound()
{
	Stop();
	m_pSound->release();
}

void CSound::Play()
{
	
	SINGLE(CSoundManager)->GetSystem()->playSound(m_pSound, nullptr, false, &m_pChannel);
	//m_pChannel->setVolume(0.1f);
}

void CSound::Stop()
{
	if(nullptr != m_pChannel)
		m_pChannel->stop();
}

void CSound::Pause()
{
	if (nullptr != m_pChannel)
		m_pChannel->setPaused(true);
}

void CSound::Resume()
{
	if (nullptr != m_pChannel)
		m_pChannel->setPaused(false);
}

void CSound::Load(const wstring& _strFilePath)
{
	FMOD_RESULT result;

	char str[255];
	wcstombs_s(nullptr, str, _strFilePath.c_str(), 255);

	result = SINGLE(CSoundManager)->GetSystem()->createSound(str, FMOD_DEFAULT, nullptr, &m_pSound);
	assert(!result);
}

void CSound::SetLoop(bool _loop)
{
	if (_loop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);
}

bool CSound::IsPlay()
{
	bool playing = false;
	if (nullptr != m_pChannel)
		m_pChannel->isPlaying(&playing);

	return playing;
}

bool CSound::IsPause()
{
	bool paused = false;
	if (nullptr != m_pChannel)
		m_pChannel->getPaused(&paused);

	return paused;
}