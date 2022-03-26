#include "pch.h"
#include "CSfx.h"

CSfx::CSfx(wstring _strKey):
	CEffect(_strKey, 0.f)
{
}

CSfx::~CSfx()
{
}

void CSfx::Update()
{
	SINGLE(CSoundManager)->Play(m_strKey);
	DELETEOBJECT(this);
}
