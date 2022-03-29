#pragma once
#include "CScene.h"
class CSceneLobby :
    public CScene
{
public:
    CSceneLobby(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CSceneLobby();

    virtual void	Update();
    virtual void    Enter();
    virtual void    Exit();

    void    LobbyInnerInit();
    void    LobbyOuterInit();

    void    CreateUI();
};

