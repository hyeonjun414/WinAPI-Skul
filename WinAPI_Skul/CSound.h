#pragma once
#include "CResource.h"
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSound :
    public CResource
{
private:
   
    Sound* m_pSound;
    Channel* m_pChannel;

public:
    CSound();
    ~CSound();

   

    void Play();
    void Stop();
    void Pause();
    void Resume();

    void Load(const wstring& _strFilePath);

    void SetLoop(bool _loop);

    bool IsPlay();
    bool IsPause();
};

