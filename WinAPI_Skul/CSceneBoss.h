#pragma once
#include "CScene.h"
class CSceneBoss :
    public CScene
{
public:
    CSceneBoss(wstring _sceneName, SCENE_TYPE _sceneType);
    virtual ~CSceneBoss();

    virtual void	Update();
    virtual void    Enter();
    virtual void    Exit();

    void    CreateUI();
};

