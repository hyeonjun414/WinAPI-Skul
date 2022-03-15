#pragma once
class CD2DImage;
class CResource;
class CSound;
class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	// 문자열을 통해 일치하는 리소스를 찾아오는 맵을 만들어준다.
	map<wstring, CResource*>		m_mapTex;
	map<wstring, CSound*>			m_mapSound;

	CSound* m_pBGM;							// BGM 리소스의 저장 변수

	map<wstring, CD2DImage*> m_mapD2DImg;	// D2D Image 리소스의 저장 자료구조

public:
	// 텍스쳐
	CTexture*	CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture*	FindTexture(const wstring& _strKey);

	// 사운드
	CSound*		LoadSound(const wstring& _strKey, const wstring _strRelativePath);
	CSound*		FindSound(const wstring& _strKey);


	CSound* LoadBGM(const wstring& _strKey, const wstring& _strRelativePath);		// BGM 불러오기 이미 있는 경우 있던 BGM 반환

	CD2DImage* FindD2DImage(const wstring& _strKey);
	CD2DImage* LoadD2DImage(const wstring& _strKey, const wstring& _strRelativePath);	// D2DImage 불러오기 이미 있는 경우 있던 D2DImage 반환
};

                     