#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;

private:
	static UINT		g_iNextID; // �浹ü ������ ID���� ������ ����

	CGameObject*	m_pOwner; // �ش� �ݶ��̴��� �����ϴ� ������Ʈ

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
	void			Render(HDC _hDC);

	void			SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	void			SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }

	CGameObject*	GetObj()			{ return m_pOwner; }
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

