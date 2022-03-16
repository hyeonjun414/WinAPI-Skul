#pragma once

class CObject;
class CAnimation;

class CAnimator
{
	friend class CObject;
private:
	map<wstring, CAnimation*>	m_mapAnim;	// �ؽ��Ŀ� ���������� ���ڿ��� �ִϸ��̼��� ����
	CAnimation*					m_pCurAnim;	// ���� ������� �ִϸ��̼�
	CAnimation*					m_pNextAnim; // ������ ������ �ִϸ��̼�
	CObject*					m_pOwner;	// �ڽ��� �������� ������Ʈ
	bool						m_bRepeat;  // �ݺ���� ����

public:
	CAnimator();
	~CAnimator();

	void Update();
	void Render(bool _bIsRight);

	void CreateAnimation( // Ư�� �ִϸ��̼��� ����
		const wstring&	_strName,			// �ִϸ��̼� �̸�
		CD2DImage*		_pImg,				// �ִϸ��̼� ��Ʋ��
		Vec2			_vLeftTop,			// �ִϸ��̼� ���� ��ǥ(���� ��� ����)
		Vec2			_vSliceSize,		// �ؽ����� ũ��
		Vec2			_vStep,				// ���� ������������ �Ÿ�
		float			_fFrameTime,		// �� ������ ������ ����ӵ�
		UINT			_iFrameCount);		// �ִϸ��̼��� ������ ������ ����

	CAnimation* FindAnimation(const wstring& _strName);		// Ư�� �ִϸ��̼��� ã�´�.
	void Play(const wstring& _strName, bool _bRepeat);				// Ư�� �ִϸ��̼��� �����Ų��.
	void PlayAndNextAnim(const wstring& _strName, bool _bRepeat, const wstring& _strNextName);
	void SetAllAnimOffset(Vec2 _vOffset);


	CObject* GetObj() { return m_pOwner; }
};

