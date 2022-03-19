#pragma once
#include "CObject.h"

class CD2DImage;

class CTile :
    public CObject
{
private:
    CD2DImage*   m_pImg;
    int         m_iX;
    int         m_iY;
    int         m_iIdx;     // 자신이 몇번째 타일인지

    TILE_TYPE   m_eType;

public:
    const static int SIZE_TILE = 64;

    CTile(OBJ_TYPE _eObjType = OBJ_TYPE::TILE);
    virtual ~CTile();
    CLONE(CTile);

    virtual void Init();
    virtual void Update();
    virtual void Render();

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    void SetType(TILE_TYPE _eType)  { m_eType = _eType; }
    void SetX(int _x)               { m_iX = _x; }
    void SetY(int _y)               { m_iY = _y; }
    void SetImage(CD2DImage* _pImg) { m_pImg = _pImg; }
    void SetImgIdx(UINT _idx)       { m_iIdx = _idx; }

    int GetIdx() { return m_iIdx; }
    int GetX() { return m_iX; }
    int GetY() { return m_iY; }
    TILE_TYPE GetType() { return m_eType; }
};

