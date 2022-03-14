#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:
	LARGE_INTEGER	m_llCurCount;	// 현재 카운트
	LARGE_INTEGER	m_llPrevCount;	// 이전 카운트
	LARGE_INTEGER	m_llFrequency;	// 초당 카운트 횟수

	bool			m_bIsSecond;	// 이번 루프가 1초로 나뉘는지
	unsigned int	m_uiPlayTime;	// 현재 플레이타임을 출력
	unsigned int	m_uiFPS;		// 초당 프레임
	double			m_dDT;			// 프레임당 초
	
public:
	void			Init();			// 타임 매니저 초기화
	void			Update();		// 매번 FPS와 DeltaTime의 연산이 되어야한다.
	
	void			SetPlayTime(unsigned int _playTime) { m_uiPlayTime = _playTime; }

	bool			GetIsSec()		{ return m_bIsSecond; }
	unsigned int	GetPlayTime()	{ return m_uiPlayTime; }	// 1프레임에 몇 초가 걸렸는지 확인
	unsigned int	GetFPS()		{ return m_uiFPS; }			// 1초에 몇번의 프레임이 나오는지 확인
	double			GetDT()			{ return m_dDT; }			// 1프레임에 몇 초가 걸렸는지 확인
	

};

