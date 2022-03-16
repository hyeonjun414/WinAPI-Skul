#pragma once

class CObject;
class CAnimation;

class CAnimator
{
	friend class CObject;
private:
	map<wstring, CAnimation*>	m_mapAnim;	// 텍스쳐와 마찬가지로 문자열로 애니메이션을 관리
	CAnimation*					m_pCurAnim;	// 현재 재생중인 애니메이션
	CAnimation*					m_pNextAnim; // 다음에 진행할 애니메이션
	CObject*					m_pOwner;	// 자신을 소유중인 오브젝트
	bool						m_bRepeat;  // 반복재생 여부

public:
	CAnimator();
	~CAnimator();

	void Update();
	void Render(bool _bIsRight);

	void CreateAnimation( // 특정 애니메이션을 생성
		const wstring&	_strName,			// 애니메이션 이름
		CD2DImage*		_pImg,				// 애니메이션 아틀라스
		Vec2			_vLeftTop,			// 애니메이션 시작 좌표(좌측 상단 기준)
		Vec2			_vSliceSize,		// 텍스쳐의 크기
		Vec2			_vStep,				// 다음 프레임으로의 거리
		float			_fFrameTime,		// 한 프레임 마다의 진행속도
		UINT			_iFrameCount);		// 애니메이션을 수행할 프레임 개수

	CAnimation* FindAnimation(const wstring& _strName);		// 특정 애니메이션을 찾는다.
	void Play(const wstring& _strName, bool _bRepeat);				// 특정 애니메이션을 실행시킨다.
	void PlayAndNextAnim(const wstring& _strName, bool _bRepeat, const wstring& _strNextName);
	void SetAllAnimOffset(Vec2 _vOffset);


	CObject* GetObj() { return m_pOwner; }
};

