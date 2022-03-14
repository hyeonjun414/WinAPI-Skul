#pragma once

class CAnimator;
class CTexture;

class CAnimation
{
	friend class CAnimator;

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;			// ����ϴ� �ؽ���
	vector<tAnimFrame>	m_vecFrame;		// ������ ����
	int					m_iCurFrame;	// ���� ������
	float				m_fFlowTime;	// ������ �ð�
	bool				m_bFinish;		// �ش� �ִϸ��̼��� �������� �Ǵ�

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

