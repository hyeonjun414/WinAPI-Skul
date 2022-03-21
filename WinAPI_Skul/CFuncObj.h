#pragma once
#include "CObject.h"

class CObject;
class CEffect;

class CFuncObj :
    public CObject
{
protected:
    CObject* m_pOwner;
    CEffect* m_pEffect;

public:
    CFuncObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath,
        float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
    virtual ~CFuncObj();

    void		SetOwner(CObject* _pObj)    { m_pOwner = _pObj; }
    CObject*    GetOwner()                  { return m_pOwner; }

};

