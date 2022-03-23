#pragma once


class CObject;
class CD2DImage;
class CAnimator;

class CCameraManager
{
	SINGLETON(CCameraManager);
private:
	Vec2			m_vCamSize;					// 카메라의 해상도
	Vec2			m_vWorldSize;				// 해당 월드 크기

	Vec2			m_vLookAt;					// 카메라가 보고있는 화면의 중심의 위치
	Vec2			m_vCurLookAt;				// 이전 프레임과 현재 프레임의 보정 위치
	Vec2			m_vPrevLookAt;				// 카메라가 보는 이전 프레임 위치

	CObject*		m_pTargetObj;				// 현재 보고 있는 오브젝트
	Vec2			m_vDiff;					// 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float			m_fTime = 1.f;				// 타겟을 따라가는데 걸리는 시간
	float			m_fFlowTime;				// 누적 시간
	float			m_fSpeed;					// 타겟을 따라가는 속도
	float			m_fPreSpeed;				// 타겟을 따라가던 속도
	float			m_fAccel;					// 타겟을 따라가는 등가속도
	float			m_fAccelRate = 100.f;		// 가속 수치

	CAM_EFFECT		m_eEffect;					// 카메라 효과를 타입
	CD2DImage*		m_pImg;						// 카메라 효과에 사용되는 텍스쳐
	float			m_fEffectDuration;			// 카메라 효과 수행시간
	float			m_fCurTime;					// 카메라 효과가 시작되고 지나간 시간
	int				m_iMagnitude;				// 카메라 흔들기 값.
	Vec2			m_vShakeAddPos;				// 효과 지속시간동안 총 흔들린 값;

	// 컴포넌트
	CAnimator*		m_pAnimator;				// 로딩에 사용할 애니메이터


private:
	void		CalDiff(); // 이전 프레임과 현재 프레임의 카메라 위치를 보간하는 함수

public:
	void		Init();
	void		Update();
	void		Render();

	void		SetLookAt(Vec2 _vLook);
	void		SetWorldSize(Vec2 _vWorldSize)		{ m_vWorldSize = _vWorldSize; }
	void		SetTarget(CObject* _pTarget)		{ m_pTargetObj = _pTarget; }
	void		SetCurLookAt(Vec2 _vLook) { m_vCurLookAt = _vLook; m_vCurLookAt = _vLook; m_vPrevLookAt = _vLook; }
	Vec2		GetLookAt()							{ return m_vLookAt; }
	Vec2		GetCurLookAt()						{ return m_vCurLookAt; }
	Vec2		GetRenderPos(Vec2 _vObjPos)			{ return _vObjPos - m_vDiff; }
	Vec2		GetRealPos(Vec2 _vRenderPos)		{ return _vRenderPos + m_vDiff; }
	CObject*	GetTarget()							{ return m_pTargetObj; }

	void		CheckBoundary();					// 현재 맵의 크기를 기준으로 카메라가 영역을 벗어나지 않도록 만드는 함수
	void		Scroll(Vec2 vec, float velocity);	// 키 입력을 받아 카메라 위치를 이동하는 함수

	void		CreateAnimator();

	// 카메라 효과들
	void		FadeIn(float _duration);
	void		FadeOut(float _duration);
	void		LodingAnimation(float _duration);
	void		CameraShaking(float _magnitude, float _duration);

	// 미니맵 출력
	void		MiniMapRender();

};

