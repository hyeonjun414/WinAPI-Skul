#pragma once
#include "CScene.h"
class CSceneInGame :
    public CScene
{
public:
    CSceneInGame();
    CSceneInGame(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CSceneInGame();

    virtual void	Update();
    virtual void    Enter();
    virtual void    Exit();
};

