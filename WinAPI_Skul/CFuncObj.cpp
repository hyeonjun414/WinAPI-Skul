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

void CFuncObj::CreateEffect(wstring _strImgName, wstring _strImgPath,
	float _fDuration, float _fPlayTime, int  _imgSize, bool _dir)
{
	CEffect* pEffect = new CEffect(OBJ_TYPE::EFFECT, _strImgName, _strImgPath, _fDuration, _fPlayTime, _imgSize, _dir);
	m_pEffect = pEffect;
	SINGLE(CSceneManager)->GetCurScene()->AddObject(pEffect);
}
