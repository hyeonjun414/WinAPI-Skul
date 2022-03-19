#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
private:
	float m_fCurTime;	// ����Ʈ�� ���۵ǰ� ������ �ð�
	float m_fDuration;	// ����Ʈ�� ���ӵǴ� �ð�

	bool  m_bIsPlay;	// ����Ʈ�� �����Ű�� ���� �����Ǿ���ϴ� ��
	
	wstring m_strKey;

public:
	CEffect(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
	virtual ~CEffect();

	virtual void Update();
	virtual void Render();

	void SetPlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	bool GetPlay()					{ return m_bIsPlay; }

	void EffectPlay(Vec2 _vPos);
};

