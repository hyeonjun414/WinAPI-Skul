#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
private:
	float m_fCurTime;
	float m_fDuration;
public:
    CEffect();
	CEffect(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, float _fDuration, int  _imgSize);
	~CEffect();


	virtual void Init();
	virtual void Update();
	virtual void Render();
};

