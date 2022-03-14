#pragma once
class CResource
{
private:
	wstring m_strKey;			// 리소스 키
	wstring m_strRelativePath;	// 리소스 상대 경로 : 절대 경로는 변할 수 있지만 상대 경로는 일정하다.

public:
	CResource();
	virtual ~CResource();

	void			SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void			SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring&	GetKey() { return m_strKey; }
	const wstring&	GetRelativePath() { return m_strRelativePath; }

};

