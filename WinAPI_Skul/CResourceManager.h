#pragma once
class CD2DImage;
class CResource;
class CSound;
class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	// ���ڿ��� ���� ��ġ�ϴ� ���ҽ��� ã�ƿ��� ���� ������ش�.
	map<wstring, CResource*>		m_mapTex;
	map<wstring, CSound*>			m_mapSound;

	CSound* m_pBGM;							// BGM ���ҽ��� ���� ����

	map<wstring, CD2DImage*> m_mapD2DImg;	// D2D Image ���ҽ��� ���� �ڷᱸ��

public:
	// �ؽ���
	CTexture*	CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture*	FindTexture(const wstring& _strKey);

	// ����
	CSound*		LoadSound(const wstring& _strKey, const wstring _strRelativePath);
	CSound*		FindSound(const wstring& _strKey);


	CSound* LoadBGM(const wstring& _strKey, const wstring& _strRelativePath);		// BGM �ҷ����� �̹� �ִ� ��� �ִ� BGM ��ȯ

	CD2DImage* FindD2DImage(const wstring& _strKey);
	CD2DImage* LoadD2DImage(const wstring& _strKey, const wstring& _strRelativePath);	// D2DImage �ҷ����� �̹� �ִ� ��� �ִ� D2DImage ��ȯ
};

                     