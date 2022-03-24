#pragma once

class CEnemy;

class CHealthBar
{
	friend class CEnemy;
private:
	CEnemy* m_pEnemy;

	CD2DImage*      m_pBackImg;
	CD2DImage*      m_pFrontImg;
	CD2DImage*		m_pFrameImg;

	Vec2			m_vOffsetPos;	// ������Ʈ������ ������� ��ġ -> �������� ������Ʈ�� �߽��̴�.
	Vec2			m_vFinalPos;	// �浹ü�� ���� ��ġ
	Vec2			m_vRenderPos;	// �׷��� ���� ��ġ
	Vec2			m_vBackScale;		// �浹ü�� ũ�� ����
	Vec2			m_vFrontScale;		// �浹ü�� ũ�� ����

public:
	CHealthBar();
	~CHealthBar();

	void			FinalUpdate();
	void			Render();

	void			SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void			SetBackScale(Vec2 _vScale) { m_vBackScale = _vScale; }
	void			SetFrontScale(Vec2 _vScale) { m_vFrontScale.x = _vScale.x; }

	CEnemy*			GetEnemy() { return m_pEnemy; }
	Vec2			GetOffsetPos() { return m_vOffsetPos; }
	Vec2			GetBackScale() { return m_vBackScale; }
	Vec2			GetFrontScale() { return m_vFrontScale; }
	Vec2			GetFinalPos() { return m_vFinalPos; }
};

