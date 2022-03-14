#pragma once
class CTexture;
class CResource;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	// 문자열을 통해 일치하는 리소스를 찾아오는 맵을 만들어준다.
	map<wstring, CResource*>		m_mapTex;
	map<wstring, CSound*>			m_mapSound;

public:
	// 텍스쳐
	CTexture*	CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture*	FindTexture(const wstring& _strKey);

	// 사운드
	CSound*		LoadSound(const wstring& _strKey, const wstring _strRelativePath);
	CSound*		FindSound(const wstring& _strKey);
};

                     