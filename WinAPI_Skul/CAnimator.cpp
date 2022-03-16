#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CObject.h"

CAnimator::CAnimator():
	m_bRepeat(false),
	m_pOwner(nullptr),
	m_pCurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::Update()
{
	// 현재 애니메이션이 지정되어있는 상태일떄
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();

		// 해당 애니메이션이 반복재생이고,
		// 이미 한차례를 수행했다면 다시 0번 프레임을 초기화한다.
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
		else if(!m_bRepeat && m_pCurAnim->IsFinish() && nullptr != m_pNextAnim )
		{
			m_pCurAnim->SetFrame(0);
			m_pCurAnim = m_pNextAnim;
			m_pNextAnim = nullptr;
			m_pCurAnim->SetFrame(0);
			m_bRepeat = true;
		}
	}
}

void CAnimator::Render(bool _bIsRight)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->Render(_bIsRight);
}


void CAnimator::CreateAnimation(const wstring& _strName, CD2DImage* _pImg, Vec2 _vLeftTop,
								Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	assert(nullptr == pAnim);

	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pImg, _vLeftTop, _vSliceSize, _vStep, _fFrameTime,_iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring,CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	if (m_pCurAnim == FindAnimation(_strName)) return;
		m_pCurAnim = FindAnimation(_strName);
	m_pCurAnim->m_iCurFrame = 0;
	m_bRepeat = _bRepeat;
}

void CAnimator::PlayAndNextAnim(const wstring& _strName, bool _bRepeat, const wstring& _strNextName)
{
	if (m_pCurAnim == FindAnimation(_strName)) return;
	m_pCurAnim = FindAnimation(_strName);
	m_pNextAnim = FindAnimation(_strNextName);
	m_pCurAnim->m_iCurFrame = 0;
	m_bRepeat = _bRepeat;
}

void CAnimator::SetAllAnimOffset(Vec2 _vOffset)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); iter++)
	{
		for (int i = 0; i < iter->second->GetMaxFrame(); i++)
		{
			iter->second->GetFrame(i).vOffset = Vec2(0.f, -m_pOwner->GetScale().y / 2) + _vOffset;
		}

	}
}
