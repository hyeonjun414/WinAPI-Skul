#pragma once
#include "CObject.h"

class CD2DImage;

class CTile :
    public CObject
{
private:
    CD2DImage*   m_pImg;
    int         m_iIdx;     // 자신이 몇번째 타일인지
    bool        m_bIsColl;  // 충돌체가 있는지

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

    void SetColl(bool _flag)        { m_bIsColl = _flag; }
    void SetImage(CD2DImage* _pImg) { m_pImg = _pImg; }
    void SetImgIdx(UINT _idx)       { m_iIdx = _idx; }
};

