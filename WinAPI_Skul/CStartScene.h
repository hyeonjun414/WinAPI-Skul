#pragma once
#include "CScene.h"
class CStartScene :
    public CScene
{
public:
    CStartScene();
    CStartScene(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CStartScene();

    virtual void    Update();
    virtual void    Render();

    virtual void    Enter();
    virtual void    Exit();
};

