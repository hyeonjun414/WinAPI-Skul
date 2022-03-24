#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
private:
	float		m_fCurTime;		// ����Ʈ�� ���۵ǰ� ������ �ð�
	float		m_fDuration;	// ����Ʈ�� ���ӵǴ� �ð�

	bool		m_bIsPlay;		// ����Ʈ�� �����Ű�� ���� �����Ǿ���ϴ� ��
	CObject*	m_pTargetObj;	// ���� ������Ʈ
	float		m_fSizeRate;

public:
	CEffect(wstring _strImgName, wstring _strImgPath, float _fDuration, float _fInterval, bool _dir);
	virtual ~CEffect();

	virtual void Update();
	virtual void Render();

	void SetTarget(CObject* _pObj) { m_pTargetObj = _pObj; }
	void SetPlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	void SetSizeRate(float _size) { m_fSizeRate = _size; }
	bool GetPlay()					{ return m_bIsPlay; }


	void EffectPlay(Vec2 _vPos);


};

