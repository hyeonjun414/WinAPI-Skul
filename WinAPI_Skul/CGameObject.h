#pragma once


class CCollider;
class CTexture;
class CAnimator;

class CGameObject
{
protected:
	wstring			m_strName;		// ������Ʈ �̸�

	OBJ_TYPE		m_eType;		// ������Ʈ Ÿ��
	bool			m_bIsActive;	// Ȱ��ȭ ����
	bool			m_bIsGravity;	// �߷� ���� ����

	Vec2			m_vPos;			// ��ġ
	Vec2			m_vRenderPos;	// ȭ��� �����ġ
	Vec2			m_vScale;		// ũ��

	// ������Ʈ
	CTexture*		m_pTex;			// �ؽ���
	CCollider*		m_pCollider;	// �浹ü
	CAnimator*		m_pAnimator;	// �ִϸ�����

public:
	CGameObject();
	CGameObject(OBJ_TYPE _eType);
	CGameObject(const CGameObject& _origin); // ���� ������
	virtual ~CGameObject();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC _hDC) = 0;

	virtual void	FinalUpdate();	// ������Ʈ�� ���� ������ ������Ʈ�� �ֻ��� Ŭ�������� �Ǵ��Ѵ�.
	virtual void	ComponentRender(HDC _hDC) final; // ������Ʈ�� �ִ� ��� ���� Ŭ�������� ������ Render���� ȣ���Ѵ�.

	void			SetName(const wstring& _strName)	{ m_strName = _strName; }
	void			SetObjGroup(OBJ_TYPE _eObjType)		{ m_eType = _eObjType; }
	void			SetActive(bool _active)				{ m_bIsActive = _active; }
	void			SetGravity(bool _active)			{ m_bIsGravity = _active; }
	void			SetPos(Vec2 _pos)					{ m_vPos = _pos; }
	void			SetScale(Vec2 _scale)				{ m_vScale = _scale; }

	const wstring&	GetName()		{ return m_strName; }
	OBJ_TYPE		GetObjGroup()	{ return m_eType; }
	bool			GetActive()		{ return m_bIsActive; }
	bool			GetGravity()	{ return m_bIsGravity; }
	Vec2			GetPos()		{ return m_vPos; }
	Vec2			GetRenderPos()	{ return m_vRenderPos; }
	Vec2			GetScale()		{ return m_vScale; }
	CTexture*		GetTexture()	{ return m_pTex; }
	CCollider*		GetCollider()	{ return m_pCollider; }
	CAnimator*		GetAnimator()	{ return m_pAnimator; }
	
	// Component
	void			TextureRender(HDC _hDC);
	void			CreateCollider();
	void			CreateAnimator();


	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther) {};
	virtual void	OnCollisionExit(CCollider* _pOther) {};

	virtual CGameObject* Clone() = 0;


	
};
