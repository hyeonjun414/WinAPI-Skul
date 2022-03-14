#pragma once

#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")


using namespace FMOD;

class CSound;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	map<wstring, CSound*> m_mapSound;	// ������� �����ϱ� ���� �ڷᱸ��

	System* m_pSystem;

public:
	void Init();
	void Update();

	void AddSound(wstring _keyName, wstring _filePath, bool _loop);
	void Play(wstring _keyName);
	void Stop(wstring _keyName);
	void Pause(wstring _keyName);
	void Resume(wstring _keyName);

	bool IsPlaySound(wstring _keyName);
	bool IsPauseSound(wstring _keyName);

	System* GetSystem() { return m_pSystem; }
};

