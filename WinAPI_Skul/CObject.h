#pragma once


class CCollider;
class CAnimator;

class CObject
{
protected:
	wstring			m_strName;		// ������Ʈ �̸�

	OBJ_TYPE		m_eType;		// ������Ʈ Ÿ��
	bool			m_bIsActive;	// Ȱ��ȭ ����
	bool			m_bIsRight;		// ������Ʈ�� ������ �����

	Vec2			m_vPos;			// ��ġ
	Vec2			m_vRenderPos;	// ȭ��� �����ġ
	Vec2			m_vScale;		// ũ��

	// ������Ʈ
	CCollider*		m_pCollider;	// �浹ü
	CAnimator*		m_pAnimator;	// �ִϸ�����

public:
	CObject();
	CObject(OBJ_TYPE _eType);
	CObject(const CObject& _origin); // ���� ������
	virtual ~CObject();

	virtual void	Init();
	virtual void	Update();
	virtual void	Render();

	virtual void	FinalUpdate();	// ������Ʈ�� ���� ������ ������Ʈ�� �ֻ��� Ŭ�������� �Ǵ��Ѵ�.
	virtual void	ComponentRender() final; // ������Ʈ�� �ִ� ��� ���� Ŭ�������� ������ Render���� ȣ���Ѵ�.
	
	void			SetName(const wstring& _strName)	{ m_strName = _strName; }
	void			SetObjType(OBJ_TYPE _eObjType)		{ m_eType = _eObjType; }
	void			SetActive(bool _active)				{ m_bIsActive = _active; }
	void			SetObjDir(bool _bDir)				{ m_bIsRight = _bDir; }
	void			SetPos(Vec2 _pos)					{ m_vPos = _pos; }
	void			SetScale(Vec2 _scale)				{ m_vScale = _scale; }
	void			SetCollider(CCollider* _pColl)		{ m_pCollider = _pColl; }

	
	const wstring&	GetName()		{ return m_strName; }
	OBJ_TYPE		GetObjType()	{ return m_eType; }
	bool			GetActive()		{ return m_bIsActive; }
	bool			GetObjDir()		{ return m_bIsRight; }
	Vec2			GetPos()		{ return m_vPos; }
	Vec2			GetRenderPos()	{ return m_vRenderPos; }
	Vec2			GetScale()		{ return m_vScale; }
	CCollider*		GetCollider()	{ return m_pCollider; }
	CAnimator*		GetAnimator()	{ return m_pAnimator; }
	
	// Component
	void			CreateCollider();
	void			CreateAnimator();


	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther) {};
	virtual void	OnCollisionExit(CCollider* _pOther) {};

	virtual CObject* Clone() { return nullptr; }


	
};

