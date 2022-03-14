#pragma once


class CGameObject;
class CTexture;

class CCameraManager
{
	SINGLETON(CCameraManager);
private:
	Vec2			m_vCamSize;					// ī�޶��� �ػ�
	Vec2			m_vWorldSize;				// �ش� ���� ũ��

	Vec2			m_vLookAt;					// ī�޶� �����ִ� ȭ���� �߽��� ��ġ
	Vec2			m_vCurLookAt;				// ���� �����Ӱ� ���� �������� ���� ��ġ
	Vec2			m_vPrevLookAt;				// ī�޶� ���� ���� ������ ��ġ

	CGameObject*	m_pTargetObj;				// ���� ���� �ִ� ������Ʈ
	Vec2			m_vDiff;					// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float			m_fTime = 1.f;				// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float			m_fFlowTime;				// ���� �ð�
	float			m_fSpeed;					// Ÿ���� ���󰡴� �ӵ�
	float			m_fPreSpeed;				// Ÿ���� ���󰡴� �ӵ�
	float			m_fAccel;					// Ÿ���� ���󰡴� ��ӵ�
	float			m_fAccelRate = 100.f;		// ���� ��ġ

	CAM_EFFECT		m_eEffect;					// ī�޶� ȿ���� Ÿ��
	CTexture*		m_pTex;						// ī�޶� ȿ���� ���Ǵ� �ؽ���
	float			m_fEffectDuration;			// ī�޶� ȿ�� ����ð�
	float			m_fCurTime;					// ī�޶� ȿ���� ���۵ǰ� ������ �ð�

private:
	void	CalDiff(); // ���� �����Ӱ� ���� �������� ī�޶� ��ġ�� �����ϴ� �Լ�

public:
	void	Init();
	void	Update();
	void	Render(HDC _hDC);

	void	SetLookAt(Vec2 _vLook);
	void	SetWorldSize(Vec2 _vWorldSize)		{ m_vWorldSize = _vWorldSize; }
	void	SetTarget(CGameObject* _pTarget)	{ m_pTargetObj = _pTarget; }
	Vec2	GetLookAt()							{ return m_vCurLookAt; }
	Vec2	GetRenderPos(Vec2 _vObjPos)			{ return _vObjPos - m_vDiff; }
	Vec2	GetRealPos(Vec2 _vRenderPos)		{ return _vRenderPos + m_vDiff; }

	void	CheckBoundary();					// ���� ���� ũ�⸦ �������� ī�޶� ������ ����� �ʵ��� ����� �Լ�
	void	Scroll(Vec2 vec, float velocity);	// Ű �Է��� �޾� ī�޶� ��ġ�� �̵��ϴ� �Լ�

	// ī�޶� ȿ����
	void	FadeIn(float _duration);
	void	FadeOut(float _duration);

};
