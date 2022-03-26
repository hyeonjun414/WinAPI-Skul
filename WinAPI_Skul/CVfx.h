#pragma once
#include "CEffect.h"
class CVfx :
    public CEffect
{
private:
	wstring m_strPath;
	float m_fSizeRate;

public:
	CVfx(wstring _strKey, wstring _strPath, float _fDuration, float _fInterval, bool _dir);
	virtual ~CVfx();

	virtual void Update();
	virtual void Render();
    void SetSizeRate(float _size) { m_fSizeRate = _size; }
};

