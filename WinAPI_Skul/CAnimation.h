#pragma once

class CAnimator;
class CD2DImage;

class CAnimation
{
	friend class CAnimator;

private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CD2DImage*			m_pImg;			// ����ϴ� �ؽ���
	vector<tAnimFrame>	m_vecFrame;		// ������ ����
	int					m_iCurFrame;	// ���� ������
	float				m_fFlowTime;	// ������ �ð�
	bool				m_bFinish;		// �ش� �ִϸ��̼��� �������� �Ǵ�

public:
	CAnimation();
	~CAnimation();

	void	Update();
	void	Render(bool _bIsRight);
	void	Render_Without_Obj();
	 
	void	Create(CD2DImage* _pImg, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount);

	void	SetName(const wstring& _strName) { m_strName = _strName; }
	void	SetFrame(int _iFrameIdx)	
	{
		m_bFinish = false;
		m_iCurFrame = _iFrameIdx; 
		m_fFlowTime = 0.f;
	}
	tAnimFrame&		GetFrame(int _iIdx) { return m_vecFrame[_iIdx]; }
	int				GetMaxFrame()		{ return (int)m_vecFrame.size(); }
	const wstring&	GetName()			{ return m_strName; }
	bool			IsFinish()			{ return m_bFinish; }
	CD2DImage*		GetImg()			{ return m_pImg; }

};

