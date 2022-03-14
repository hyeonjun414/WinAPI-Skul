#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	LARGE_INTEGER	m_llCurCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llPrevCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��

	bool			m_bIsSecond;	// �̹� ������ 1�ʷ� ��������
	unsigned int	m_uiPlayTime;	// ���� �÷���Ÿ���� ���
	unsigned int	m_uiFPS;		// �ʴ� ������
	double			m_dDT;			// �����Ӵ� ��
	
public:
	void			Init();			// Ÿ�� �Ŵ��� �ʱ�ȭ
	void			Update();		// �Ź� FPS�� DeltaTime�� ������ �Ǿ���Ѵ�.
	
	void			SetPlayTime(unsigned int _playTime) { m_uiPlayTime = _playTime; }

	bool			GetIsSec()		{ return m_bIsSecond; }
	unsigned int	GetPlayTime()	{ return m_uiPlayTime; }	// 1�����ӿ� �� �ʰ� �ɷȴ��� Ȯ��
	unsigned int	GetFPS()		{ return m_uiFPS; }			// 1�ʿ� ����� �������� �������� Ȯ��
	double			GetDT()			{ return m_dDT; }			// 1�����ӿ� �� �ʰ� �ɷȴ��� Ȯ��
	

};

