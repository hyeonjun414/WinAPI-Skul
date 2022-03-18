#pragma once
#include "CObject.h"



class CD2DImage;

class CImageObj :
    public CObject
{
	CD2DImage*  m_pImg;
	bool		m_bRenderStyle;
	IMG_EFFECT  m_eEffectType;
	float		m_fAlpha;
	float		m_fDepthLevel;

	float		m_fEffectDuration;			// �̹��� ȿ�� ����ð�
	float		m_fCurTime;					// �̹��� ȿ���� ���۵ǰ� ������ �ð�
	bool		m_bEffectSwitch;				// ȿ���� �ݺ� ������ ���� ����

public:
	CImageObj();
	CImageObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle);
	~CImageObj();

	
	CD2DImage* GetImage() { return m_pImg; }

	virtual CImageObj* Clone();
	virtual void Update();
	virtual void Render();

	void	SetEffectType(IMG_EFFECT _eType) { m_eEffectType = _eType; }
	void	SetDepth(float _fLevel) { m_fDepthLevel = _fLevel; }
};

