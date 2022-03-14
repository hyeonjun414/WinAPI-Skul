#pragma once

class CAnimator;
class CTexture;

class CAnimation
{
	friend class CAnimator;

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;			// 사용하는 텍스쳐
	vector<tAnimFrame>	m_vecFrame;		// 프레임 정보
	int					m_iCurFrame;	// 현재 프레임
	float				m_fFlowTime;	// 지나간 시간
	bool				m_bFinish;		// 해당 애니메이션이 끝났는지 판단

public:
	CAnimation();
	~CAnimation();

	void Update();
	void Render(HDC _hDC);

	void Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount);

	void SetName(const wstring& _strName) { m_strName = _strName; }
	void	SetFrame(int _iFrameIdx)	
	{
		m_bFinish = false;
		m_iCurFrame = _iFrameIdx; 
		m_fFlowTime = 0.f;
	}
	tAnimFrame& GetFrame(int _iIdx) { return m_vecFrame[_iIdx]; }
	int			GetMaxFrame()		{ return (int)m_vecFrame.size(); }
	const wstring&	GetName()	{ return m_strName; }
	bool			IsFinish() { return m_bFinish; }

};

