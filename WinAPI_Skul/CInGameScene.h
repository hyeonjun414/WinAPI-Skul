#pragma once
#include "CScene.h"
class CInGameScene :
    public CScene
{
public:
    CInGameScene();
    CInGameScene(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CInGameScene();

    virtual void	Update();
    virtual void    Enter();
    virtual void    Exit();
};

