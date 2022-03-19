#pragma once
#include "CScene.h"
class CSceneStart :
    public CScene
{
public:
    CSceneStart();
    CSceneStart(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CSceneStart();

    virtual void    Update();
    virtual void    Render();

    virtual void    Enter();
    virtual void    Exit();
};

