#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CGameObject.h"

CAnimation::CAnimation() :
	m_strName(L""),
	m_pAnimator(nullptr),
	m_pTex(nullptr),
	m_iCurFrame(0),
	m_fFlowTime(0.f),
	m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	// 렉이 걸려서 DT가 급격히 쌓이면 프레임이 빠르게 진행될 수 있다.
	// 이를 해결하려면 누적된 Dt값을 1이하로 만들어 다음 프레임으로 한번에 건너뛰도록 반복문으로 처리할것.
	
	// 만약 애니메이션이 끝난 상태라면 업데이트를 진행하지 않는다.
	if (m_bFinish) return;

	m_fFlowTime += DT;

	// 누적된 시간이 현재 프레임의 진행 시간을 넘어서면 다음 프레임으로 넘긴다.
	if (m_fFlowTime > m_vecFrame[m_iCurFrame].fFrameTime)
	{
		++m_iCurFrame;

		// 애니메이션의 마지막 프레임에 도달했다면
		if (m_vecFrame.size() <= m_iCurFrame)
		{
			// 현재 프레임을 끝났다고 표시시킨다.
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fFlowTime = 0.f;
			return;
		}

		// 남는 시간의 오차가 일어나지 않도록 0으로 초기화하는것이 아닌 잔여시간을 남겨준다.
		m_fFlowTime -= m_vecFrame[m_iCurFrame].fFrameTime;
	}
}

void CAnimation::Render(HDC _hDC)
{
	if (m_bFinish) return; // 애니메이션이 끝났다면 렌더도 진행하지 않는다.

	// 애니메이션을 출력할 위치를 가져온다.
	CGameObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetRenderPos();

	// 오브젝트의 위치값에 더해 애니메이션의 위치 오프셋 값을 더해준다.
	vPos += m_vecFrame[m_iCurFrame].vOffset;

	TransparentBlt(_hDC,
		(int)(vPos.x - m_vecFrame[m_iCurFrame].vSliceSize.x / 2.f), // 좌상단 위치 찾기
		(int)(vPos.y - m_vecFrame[m_iCurFrame].vSliceSize.y / 2.f), 
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // 프레임 크기만큼 출력
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.y),
		m_pTex->GetDC(),
		(int)(m_vecFrame[m_iCurFrame].vLT.x), // 해당 텍스쳐내에서 잘라내기를 시작할 좌상단 좌표
		(int)(m_vecFrame[m_iCurFrame].vLT.y),
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // 잘라낼 크기
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.y),
		RGB(255,0,255));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frame = {};
	for (int i = 0; i < (int)_iFrameCount; i++)
	{
		frame.fFrameTime = _fFrameTime;
		frame.vSliceSize = _vSliceSize;
		frame.vLT = _vLeftTop + _vStep * i; // 프레임 별 좌상단

		m_vecFrame.push_back(frame);
	}
}
