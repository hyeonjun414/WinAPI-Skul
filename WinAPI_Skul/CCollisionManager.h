#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT leftId;
		UINT rightId;
	};
	ULONGLONG ID;
};


class CCollisionManager
{
	SINGLETON(CCollisionManager);

private:
	map<ULONGLONG, bool>	m_mapColInfo;						// 충돌체 간의 이전 프레임 충돌 정보
	UINT					m_arrCheck[(UINT)OBJ_TYPE::SIZE];	// 오브젝트 타입간의 충돌 여부를 확인하는 배열

public:
	void	Init();
	void	Update();

	void	CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);		// 두 오브젝트 타입간의 충돌을 적용
	void	UnCheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);	// 두 오브젝트 타입간의 충돌을 해제
	void	Reset();											// 등록된 충복정보를 초기화하는 함수

private:
	void	CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);	// 두 오브젝트 타입 오브젝트들의 충돌 여부를 확인
	bool	IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);	// 충돌 여부를 확인하는 함수
};

