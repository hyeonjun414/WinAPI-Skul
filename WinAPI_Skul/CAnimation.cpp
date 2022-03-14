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

void CAnimation::Render(HDC _hDC)
{
	if (m_bFinish) return; // �ִϸ��̼��� �����ٸ� ������ �������� �ʴ´�.

	// �ִϸ��̼��� ����� ��ġ�� �����´�.
	CGameObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetRenderPos();

	// ������Ʈ�� ��ġ���� ���� �ִϸ��̼��� ��ġ ������ ���� �����ش�.
	vPos += m_vecFrame[m_iCurFrame].vOffset;

	TransparentBlt(_hDC,
		(int)(vPos.x - m_vecFrame[m_iCurFrame].vSliceSize.x / 2.f), // �»�� ��ġ ã��
		(int)(vPos.y - m_vecFrame[m_iCurFrame].vSliceSize.y / 2.f), 
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // ������ ũ�⸸ŭ ���
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.y),
		m_pTex->GetDC(),
		(int)(m_vecFrame[m_iCurFrame].vLT.x), // �ش� �ؽ��ĳ����� �߶󳻱⸦ ������ �»�� ��ǥ
		(int)(m_vecFrame[m_iCurFrame].vLT.y),
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // �߶� ũ��
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
		frame.vLT = _vLeftTop + _vStep * i; // ������ �� �»��

		m_vecFrame.push_back(frame);
	}
}
