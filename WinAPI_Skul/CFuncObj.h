#pragma once
#include "CObject.h"

class CObject;
class CEffect;

class CFuncObj :
    public CObject
{
private:
    CObject* m_pOwner;
    CEffect* m_pEffect;

public:
    CFuncObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath,
        float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
    virtual ~CFuncObj();

    void		SetOwner(CObject* _pObj)    { m_pOwner = _pObj; }
    void        SetEffect(CEffect* _pEffect) { m_pEffect = _pEffect; }

    CObject*    GetOwner()                  { return m_pOwner; }
    CEffect*    GetEffect()                 { return m_pEffect; }

    void        CreateEffect(wstring _strImgName, wstring _strImgPath,
        float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);


};

