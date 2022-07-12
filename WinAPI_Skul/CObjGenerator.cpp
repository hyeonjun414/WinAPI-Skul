#include "pch.h"
#include "CObjGenerator.h"

CObjGenerator::CObjGenerator(float _delay, Vec2 _pos, Vec2 _areaSize, float _reservTime):
	CObject(OBJ_TYPE::GENERATOR),
	m_vecObject{},
	m_vecVfx{},
	m_vecSfx{},
	m_fDelayTime(_delay),
	m_fCurTime(0.f),
	m_vGenerateArea(_areaSize),
	m_fReservTime(_reservTime)
{
	SetPos(_pos);
}

CObjGenerator::~CObjGenerator()
{

}

void CObjGenerator::Init()
{
}

void CObjGenerator::Update()
{
	m_fReservTime -= DT;
	if (m_fReservTime <= 0)
	{
		if (m_vecObject.size() == 0)
			DELETEOBJECT(this); // 예약된 오브젝트가 전부 생성되었다면 해당 객체 삭제

		m_fCurTime += DT;

		if (m_fCurTime >= m_fDelayTime)
		{
			m_fCurTime = 0.f;
			// 오브젝트를 차례대로 꺼내옴.
			CObject* pObj = m_vecObject[m_vecObject.size() - 1];
			m_vecObject.pop_back();

			Vec2 randPos = Vec2(m_vPos.x + rand() % (int)m_vGenerateArea.x - m_vGenerateArea.x / 2,
				m_vPos.y + rand() % (int)m_vGenerateArea.y - m_vGenerateArea.y / 2);
			pObj->SetPos(randPos);
			CREATEOBJECT(pObj); // 랜덤 위치에 오브젝트 생성.
			
			// 순서에 맞게 이펙트와 효과음을 생성.
			if (m_vecVfx.size() != 0)
			{
				CEffect* pEft = m_vecVfx[m_vecVfx.size() - 1];
				m_vecVfx.pop_back();
				CREATEOBJECT((CObject*)pEft);
			}
			if (m_vecSfx.size() != 0)
			{
				CEffect* pEft = m_vecSfx[m_vecSfx.size() - 1];
				m_vecSfx.pop_back();
				CREATEOBJECT((CObject*)pEft);
			}
		}
	}
}

