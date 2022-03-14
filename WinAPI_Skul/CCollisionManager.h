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
	map<ULONGLONG, bool>	m_mapColInfo;						// �浹ü ���� ���� ������ �浹 ����
	UINT					m_arrCheck[(UINT)OBJ_TYPE::SIZE];	// ������Ʈ Ÿ�԰��� �浹 ���θ� Ȯ���ϴ� �迭

public:
	void	Init();
	void	Update();

	void	CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);		// �� ������Ʈ Ÿ�԰��� �浹�� ����
	void	UnCheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);	// �� ������Ʈ Ÿ�԰��� �浹�� ����
	void	Reset();											// ��ϵ� �溹������ �ʱ�ȭ�ϴ� �Լ�

private:
	void	CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);	// �� ������Ʈ Ÿ�� ������Ʈ���� �浹 ���θ� Ȯ��
	bool	IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);	// �浹 ���θ� Ȯ���ϴ� �Լ�
};

