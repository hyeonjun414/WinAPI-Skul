#include "pch.h"
#include "CFuncObj.h"
#include "CEffect.h"
#include "CScene.h"

CFuncObj::CFuncObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath,
	float _fDuration, float _fPlayTime, int _imgSize, bool _dir) :
	CObject(_eType)
{

}

CFuncObj::~CFuncObj()
{
	if (nullptr != m_pEffect)
		m_pEffect->SetPlay(false);
}

