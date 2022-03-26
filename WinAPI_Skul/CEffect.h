#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
protected:
	wstring		m_strKey;		
	float		m_fCurTime;		// ����Ʈ�� ���۵ǰ� ������ �ð�
	float		m_fDuration;	// ����Ʈ�� ���ӵǴ� �ð�

public:
	CEffect(wstring _strKey, float _fDuration);
	virtual ~CEffect();

	virtual void Update() = 0;
	virtual void Render() {}


};

