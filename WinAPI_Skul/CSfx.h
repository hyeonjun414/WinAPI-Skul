#pragma once
#include "CEffect.h"
class CSfx :
    public CEffect
{

public:
	CSfx(wstring _strKey);
	virtual ~CSfx();

	virtual void Update();
};

