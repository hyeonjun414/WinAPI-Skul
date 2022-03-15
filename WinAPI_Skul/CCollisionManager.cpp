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
	Reset(); // �浹������ �ʱ�ȭ�Ѵ�.
}

void CCollisionManager::Update()
{
	// ���� �׷� ������ŭ �˻��Ѵ�.
	for (UINT iRow = 0; iRow < (UINT)OBJ_TYPE::SIZE; iRow++)
	{
		// ���� �׷� ������ŭ �˻��Ѵ�.
		for (UINT iCol = iRow;  iCol < (UINT)OBJ_TYPE::SIZE;  iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// ���� ������ �浹ó���� ������ ������Ʈ�� �����´�.
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
	// ���� �� ������.
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;

	for (int i = 0; i < (int)vecLeft.size(); i++)
	{
		// ���� ������Ʈ�� �浹ü�� ���� ��� ����,
		if (nullptr == vecLeft[i]->GetCollider()) 
			continue;

		for (int j = 0; j < (int)vecRight.size(); j++)
		{
			// ������ ������Ʈ�� �浹ü�� ���� ��� ����,
			// �ڱ� �ڽŰ��� �浹�� ����
			// ���� ���� ������Ʈ�� ������ ������Ʈ�� ���� �ּҸ� ����Ű��
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();


			// �� �浹ü ���� ���̵� ����
			// �� ���̵� �Ϸķ� ������ �ڵ带 ���� �浹 �ڵ�� ����� �����Ѵ�.
			COLLIDER_ID ID;
			ID.leftId = pLeftCol->GetID();
			ID.rightId = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID); // �浹�� ������ �ִ��� Ȯ���Ѵ�.

			// �߰ߵ� ���� �浹������ ������
			if (m_mapColInfo.end() == iter)
			{
				// ���� ���� ���ٸ�
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// �� ������Ʈ�� �浹�ߴ��� Ȯ��,
			// Ű ���¿� ���������� ���� �������� �浹������ �ʿ��ϴ�.
			if (IsCollision(pLeftCol,pRightCol))
			{
				// ���� �浹 ���̴�.
				if (iter->second)
				{
					// ���� �����ӿ��� �浹�� �Ͼ���ٸ�.

					if (!vecLeft[i]->GetActive() || !vecRight[j]->GetActive())
					{
						// �� �� �ϳ��� ���� �����̶��, �浹 ���������ش�.
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
					// �̹� �浹�� ó�� �Ͼ �浹�̶��
					// �� ������Ʈ ��� ���� ������ �ƴ϶�� ����
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
					// ������ �浹�� �Ͼ���� ������ �浹���� �ʾ��� ���
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
	// �� �浹ü�� ���� �������� ���� ��ġ�� ũ�� ������ �����;� �Ѵ�.
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
