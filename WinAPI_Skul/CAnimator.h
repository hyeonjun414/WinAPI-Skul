#pragma once

class CGameObject;
class CAnimation;

class CAnimator
{
	friend class CGameObject;
private:
	map<wstring, CAnimation*>	m_mapAnim;	// �ؽ��Ŀ� ���������� ���ڿ��� �ִϸ��̼��� ����
	CAnimation*					m_pCurAnim;	// ���� ������� �ִϸ��̼�
	CGameObject*				m_pOwner;	// �ڽ��� �������� ������Ʈ
	bool						m_bRepeat;  // �ݺ���� ����

public:
	CAnimator();
	~CAnimator();

	void Update();
	void Render(HDC _hDC);

	void CreateAnimation( // Ư�� �ִϸ��̼��� ����
		const wstring&	_strName,			// �ִϸ��̼� �̸�
		CTexture*		_pTex,				// �ִϸ��̼� ��Ʋ��
		Vec2			_vLeftTop,			// �ִϸ��̼� ���� ��ǥ(���� ��� ����)
		Vec2			_vSliceSize,		// �ؽ����� ũ��
		Vec2			_vStep,				// ���� ������������ �Ÿ�
		float			_fFrameTime,		// �� ������ ������ ����ӵ�
		UINT			_iFrameCount);		// �ִϸ��̼��� ������ ������ ����

	CAnimation* FindAnimation(const wstring& _strName);		// Ư�� �ִϸ��̼��� ã�´�.
	void Play(const wstring& _strName, bool _bRepeat);				// Ư�� �ִϸ��̼��� �����Ų��.

	void SetAllAnimOffset();


	CGameObject* GetObj() { return m_pOwner; }
};

