#include "pch.h"
#include "CCollisionManager.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager():
	m_mapColInfo{},
	m_arrCheck{}
{}
CCollisionManager::~CCollisionManager()
{}

void CCollisionManager::Init()
{
	Reset(); // 충돌정보를 초기화한다.
}

void CCollisionManager::Update()
{
	// 행을 그룹 개수만큼 검사한다.
	for (UINT iRow = 0; iRow < (UINT)OBJ_TYPE::SIZE; iRow++)
	{
		// 열을 그룹 개수만큼 검사한다.
		for (UINT iCol = iRow;  iCol < (UINT)OBJ_TYPE::SIZE;  iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// 현재 씬에서 충돌처리를 수행할 오브젝트를 가져온다.
				CollisionGroupUpdate((OBJ_TYPE)iRow, (OBJ_TYPE)iCol);
			}
		}
	}
}

void CCollisionManager::CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	
	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionManager::UnCheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	m_arrCheck[iRow] &= ~(1 << iCol);
}

void CCollisionManager::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJ_TYPE::SIZE);
}

void CCollisionManager::CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{
	// 현재 씬 가져옴.
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	for (int i = 0; i < (int)vecLeft.size(); i++)
	{
		// 왼쪽 오브젝트가 충돌체가 없을 경우 다음,
		if (nullptr == vecLeft[i]->GetCollider()) 
			continue;

		for (int j = 0; j < (int)vecRight.size(); j++)
		{
			// 오른쪽 오브젝트가 충돌체가 없을 경우 다음,
			// 자기 자신과의 충돌을 방지
			// 만약 왼쪽 오브젝트와 오른쪽 오브젝트가 같은 주소를 가리키면
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();


			// 두 충돌체 조합 아이디 생성
			// 두 아이디를 일렬로 조합한 코드를 고유 충돌 코드로 만들어 관리한다.
			COLLIDER_ID ID;
			ID.leftId = pLeftCol->GetID();
			ID.rightId = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID); // 충돌된 정보가 있는지 확인한다.

			// 발견된 이전 충돌정보가 없으면
			if (m_mapColInfo.end() == iter)
			{
				// 정보 조차 없다면
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 두 오브젝트가 충돌했는지 확인,
			// 키 상태와 마찬가지로 이전 프레임의 충돌정보가 필요하다.
			if (IsCollision(pLeftCol,pRightCol))
			{
				// 현재 충돌 중이다.
				if (iter->second)
				{
					// 이전 프레임에도 충돌이 일어났었다면.

					if (!vecLeft[i]->GetActive() || !vecRight[j]->GetActive())
					{
						// 둘 중 하나가 삭제 예정이라면, 충돌 해제시켜준다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}

					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
				{
					// 이번 충돌이 처음 일어난 충돌이라면
					// 두 오브젝트 모두 삭제 예정이 아니라면 실행
					if (vecLeft[i]->GetActive() && vecRight[j]->GetActive())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					// 이전에 충돌이 일어났지만 지금은 충돌되지 않았을 경우
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}

		}
	}
}

bool CCollisionManager::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// 각 충돌체의 현재 프레임의 최종 위치와 크기 정보를 가져와야 한다.
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();
	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f &&
		abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
	return false;
}
