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
	void Render(bool _bIsRight, float _rate = 1.0f);
	void Render_Without_Obj();

	void CreateAnimation( // Ư�� �ִϸ��̼��� ����
		const wstring&	_strName,			// �ִϸ��̼� �̸�
		CD2DImage*		_pImg,				// �ִϸ��̼� ��Ʋ��
		Vec2			_vLeftTop,			// �ִϸ��̼� ���� ��ǥ(���� ��� ����)
		Vec2			_vSliceSize,		// �ؽ����� ũ��
		Vec2			_vStep,				// ���� ������������ �Ÿ�
		float			_fFrameTime,		// �� ������ ������ ����ӵ�
		UINT			_iFrameCount);		// �ִϸ��̼��� ������ ������ ����

	void CreateAnim(
		const wstring& _strName,
		const wstring& _strPath,
		float _fInterval);

	CAnimation* FindAnimation(const wstring& _strName);		// Ư�� �ִϸ��̼��� ã�´�.
	void Play(const wstring& _strName, bool _bRepeat);				// Ư�� �ִϸ��̼��� �����Ų��.
	void PlayAndNextAnim(const wstring& _strName, bool _bRepeat, const wstring& _strNextName);
	void SetAllAnimOffset(Vec2 _vOffset);
	
	CAnimation* GetCurAnim() { return m_pCurAnim; }

	CObject* GetObj() { return m_pOwner; }
};

