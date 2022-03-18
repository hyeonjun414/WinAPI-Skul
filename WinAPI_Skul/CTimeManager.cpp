#include "pch.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager() :
	m_llCurCount{},
	m_llPrevCount{},
	m_llFrequency{},
	m_uiFPS(0),
	m_dDT(0),
	m_fPlayTime(0)
{}

CTimeManager::~CTimeManager()
{}

void CTimeManager::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);		// 현재 시간의 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);	// 1초당 진행하는 카운트 수
}


void CTimeManager::Update()
{
	static unsigned int updateCount = 0;
	static double updateOneSecond = 0;

	QueryPerformanceCounter(&m_llCurCount); // 현재 카운트 갱신

	// 카운트 간의 차이 값을 1초당 진행한 카운트로 나누어준다. -> 업데이트 사이에 몇초가 지났는지 알 수 있음.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount; // 이전 카운트 갱신

	// 1초에 몇번 업데이트를 하나.
	++updateCount;
	updateOneSecond += m_dDT;

	m_fPlayTime += DT;

	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;
		m_bIsSecond = true;

		updateOneSecond = 0;
		updateCount = 0;
	}
	else
	{
		m_bIsSecond = false;
	}
}

