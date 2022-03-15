#pragma once

class CObject;

class CCollider
{
	friend class CObject;

private:
	static UINT		g_iNextID; // �浹ü ������ ID���� ������ ����

	CObject*	m_pOwner; // �ش� �ݶ��̴��� �����ϴ� ������Ʈ

	Vec2			m_vOffsetPos;	// ������Ʈ������ ������� ��ġ -> �������� ������Ʈ�� �߽��̴�.
	Vec2			m_vFinalPos;	// �浹ü�� ���� ��ġ
	Vec2			m_vRenderPos;	// �׷��� ���� ��ġ
	Vec2			m_vScale;		// �浹ü�� ũ�� ����

	UINT			m_uiID;			// �浹ü�� ������ ID
	UINT			m_uiColCount;	// �浹ü�� �浹 Ƚ��

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	void			FinalUpdate();
	void			Render();

	void			SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	void			SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }

	CObject*	GetObj()			{ return m_pOwner; }
	Vec2			GetOffsetPos()		{ return m_vOffsetPos; }
	Vec2			GetScale()			{ return m_vScale; }
	UINT			GetID()				{ return m_uiID; }
	Vec2			GetFinalPos()		{ return m_vFinalPos; }

	// ���� �����ڰ� �۵����� �ʵ��� ������ش�.
	CCollider& operator = (const CCollider& _origin) = delete;

	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹�� ���۵ɶ� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther); // �⵹�� ������ ȣ��Ǵ� �Լ�
	
};

