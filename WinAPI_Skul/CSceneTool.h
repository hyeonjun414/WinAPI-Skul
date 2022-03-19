#pragma once
#include "CScene.h"

class CUIButton;
class CUITileBtn;

class CSceneTool :
    public CScene
{
private:

    CD2DImage* m_pMapImg;

    HWND    m_hWnd;
    UINT    m_iIdx;
    TILE_TYPE m_eTileType;
    float   m_velocity;
    bool    m_bIsTileCol;

    UINT m_iTileX;
    UINT m_iTileY;

public:
    CSceneTool();
    CSceneTool(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CSceneTool();


    virtual void Update();
    virtual void Render();
    virtual void Enter();
    virtual void Exit();

    void SetIdx(UINT _idx);
    void SetTileColl(bool _bTileColl);
    void SetTileIdx();		// 마우스와 상호작용해서 타일을 바꿈.
    void SetGroup(TILE_TYPE _eTileType) { m_eTileType = _eTileType; }
    void SetTileGroup();

    void CreateTile(UINT xSize, UINT ySize);
    void SaveTile(const wstring& _strPath);
    void LoadTile(const wstring& _strPath);
    void SaveTileData();
    void LoadTileData();
    void LoadMap();

    void ClickTileGroup(CUIButton* _btn);
    void ClickTile(CUITileBtn* _btn);

private:
    void CreateTilePanel();
    void PrintMap();
    void PrintTileLine();
    void PrintTileGroup();

};
