#pragma once
#include "CScene.h"
class CToolScene :
    public CScene
{
private:
    HWND    m_hWnd;
    UINT    m_iIdx;
    float   m_velocity;
    bool    m_bIsTileCol;

public:
    CToolScene();
    CToolScene(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CToolScene();


    virtual void Update();
    virtual void Enter();
    virtual void Exit();

    void SetIdx(UINT _idx);
    void SetTileColl(bool _bTileColl);
    void SetTileIdx();		// 마우스와 상호작용해서 타일을 바꿈.

    void SaveTile(const wstring& _strPath);
    void SaveTileData();
    void LoadTileData();


};
