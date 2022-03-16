#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CD2DImage.h"
#include "CObject.h"

CAnimation::CAnimation() :
	m_strName(L""),
	m_pAnimator(nullptr),
	m_pImg(nullptr),
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
	// ���� �ɷ��� DT�� �ް��� ���̸� �������� ������ ����� �� �ִ�.
	// �̸� �ذ��Ϸ��� ������ Dt���� 1���Ϸ� ����� ���� ���������� �ѹ��� �ǳʶٵ��� �ݺ������� ó���Ұ�.
	
	// ���� �ִϸ��̼��� ���� ���¶�� ������Ʈ�� �������� �ʴ´�.
	if (m_bFinish) return;

	m_fFlowTime += DT;

	// ������ �ð��� ���� �������� ���� �ð��� �Ѿ�� ���� ���������� �ѱ��.
	if (m_fFlowTime > m_vecFrame[m_iCurFrame].fFrameTime)
	{
		++m_iCurFrame;

		// �ִϸ��̼��� ������ �����ӿ� �����ߴٸ�
		if (m_vecFrame.size() <= m_iCurFrame)
		{
			// ���� �������� �����ٰ� ǥ�ý�Ų��.
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fFlowTime = 0.f;
			return;
		}

		// ���� �ð��� ������ �Ͼ�� �ʵ��� 0���� �ʱ�ȭ�ϴ°��� �ƴ� �ܿ��ð��� �����ش�.
		m_fFlowTime -= m_vecFrame[m_iCurFrame].fFrameTime;
	}
}

void CAnimation::Render(bool _bIsRight)
{
	if (m_bFinish) return; // �ִϸ��̼��� �����ٸ� ������ �������� �ʴ´�.

	// �ִϸ��̼��� ����� ��ġ�� �����´�.
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetRenderPos();

	// ������Ʈ�� ��ġ���� ���� �ִϸ��̼��� ��ġ ������ ���� �����ش�.
	vPos += m_vecFrame[m_iCurFrame].vOffset;
	if (_bIsRight)
	{
		RENDER->RenderFrame(
			m_pImg,
			vPos.x - m_vecFrame[m_iCurFrame].vSliceSize.x,
			vPos.y - m_vecFrame[m_iCurFrame].vSliceSize.y,
			vPos.x + m_vecFrame[m_iCurFrame].vSliceSize.x,
			vPos.y + m_vecFrame[m_iCurFrame].vSliceSize.y,
			m_vecFrame[m_iCurFrame].vLT.x,
			m_vecFrame[m_iCurFrame].vLT.y,
			m_vecFrame[m_iCurFrame].vLT.x + m_vecFrame[m_iCurFrame].vSliceSize.x,
			m_vecFrame[m_iCurFrame].vLT.y + m_vecFrame[m_iCurFrame].vSliceSize.y,
			1.0f);
	}
	else
	{
		RENDER->RenderRevFrame(
			m_pImg,
			vPos.x - m_vecFrame[m_iCurFrame].vSliceSize.x,
			vPos.y - m_vecFrame[m_iCurFrame].vSliceSize.y,
			vPos.x + m_vecFrame[m_iCurFrame].vSliceSize.x,
			vPos.y + m_vecFrame[m_iCurFrame].vSliceSize.y,
			m_vecFrame[m_iCurFrame].vLT.x,
			m_vecFrame[m_iCurFrame].vLT.y,
			m_vecFrame[m_iCurFrame].vLT.x + m_vecFrame[m_iCurFrame].vSliceSize.x,
			m_vecFrame[m_iCurFrame].vLT.y + m_vecFrame[m_iCurFrame].vSliceSize.y,
			1.0f);
	}

}

void CAnimation::Create(CD2DImage* _pImg, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount)
{
	m_pImg = _pImg;

	tAnimFrame frame = {};
	for (int i = 0; i < (int)_iFrameCount; i++)
	{
		frame.fFrameTime = _fFrameTime;
		frame.vSliceSize = _vSliceSize;
		frame.vLT = _vLeftTop + _vStep * i; // ������ �� �»��

		m_vecFrame.push_back(frame);
	}
}
