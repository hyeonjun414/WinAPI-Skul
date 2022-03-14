#pragma once
class CResource
{
private:
	wstring m_strKey;			// ���ҽ� Ű
	wstring m_strRelativePath;	// ���ҽ� ��� ��� : ���� ��δ� ���� �� ������ ��� ��δ� �����ϴ�.

public:
	CResource();
	virtual ~CResource();

	void			SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void			SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring&	GetKey() { return m_strKey; }
	const wstring&	GetRelativePath() { return m_strRelativePath; }

};

