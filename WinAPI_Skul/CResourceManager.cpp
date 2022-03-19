#include "pch.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSound.h"
#include "CD2DImage.h"

CResourceManager::CResourceManager():
	m_mapTex{},
	m_mapSound{},
	m_pBGM(nullptr),
	m_mapD2DImg{}
{}

CResourceManager::~CResourceManager()
{
	// �ҷ��� ���ҽ����� �޸� ���� ��Ų��.
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
	Safe_Delete_Map(m_mapD2DImg);
}

CTexture* CResourceManager::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;

	pTex = new CTexture();
	pTex->Create(_width, _height);
	pTex->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �ؽ��ĸ� ���� Ž���غ��� �ִٸ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;


	// �ҷ��� �ؽ��İ� ���ٸ� �ҷ����� ������ �����ϰ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.
	wstring strFilePath = SINGLE(CPathManager)->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);

	// �ؽ��ĸ� ã�� ���ߴٸ� ������Ʈ ��ȯ
	if (iter == m_mapTex.end()) 
		return nullptr;

	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{
	// ���带 ���� Ž���غ��� �ִٸ� �ش� ���带 ��ȯ�Ѵ�.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound) return pSound;

	// �ҷ��� ���尡 ���ٸ� �ҷ����� ������ �����ϰ� �ش� ���带 ��ȯ�Ѵ�.
	wstring strFilePath = SINGLE(CPathManager)->GetContextRelativePath();
	strFilePath += _strRelativePath;

	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	// ���带 ã�� ���ߴٸ� ������Ʈ ��ȯ
	if (iter == m_mapSound.end()) 
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResourceManager::LoadBGM(const wstring& _strKey, const wstring& _strRelativePath)
{
	return nullptr;
}

CD2DImage* CResourceManager::FindD2DImage(const wstring& _strKey)
{
	// CD2DImage Ű ���� ���� Ž��
	map<wstring, CD2DImage*>::iterator iter = m_mapD2DImg.find(_strKey);

	if (m_mapD2DImg.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CD2DImage* CResourceManager::LoadD2DImage(const wstring& _strKey, const wstring& _strRelativePath)
{
	CD2DImage* pD2DImg = FindD2DImage(_strKey);
	if (nullptr != pD2DImg)
		return pD2DImg;

	wstring strFilePath = SINGLE(CPathManager)->GetContextRelativePath();
	strFilePath += _strRelativePath;

	CD2DImage* img = new CD2DImage;

	IWICBitmapDecoder* p_decoder;		// ����� �̹����� ������ ��ü
	IWICBitmapFrameDecode* p_frame;		// Ư�� �׸��� ������ ��ü
	IWICFormatConverter* p_converter;	// �̹��� ��ȯ ��ü

	// WIC�� Factory ��ü�� ����Ͽ� �̹��� ���� ������ ���� ��ü�� ����
	if (S_OK != SINGLE(CRenderManager)->GetImageFactory()->CreateDecoderFromFilename(strFilePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// ������ �����ϴ� �̹��� �߿��� ù��° �̹����� �����Ѵ�.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap������ ��Ʈ���� ID2D1Bitmap. �������� ��ȯ�ϱ� ���� ��ü ����
	if (S_OK != SINGLE(CRenderManager)->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ ����
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� ����
	ID2D1Bitmap* bitmap = SINGLE(CRenderManager)->GetBitmap();
	if (S_OK != SINGLE(CRenderManager)->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// ���������� ������ ���
	img->SetImage(bitmap);
	img->SetKey(_strKey);
	img->SetRelativePath(_strRelativePath);
	m_mapD2DImg.insert(make_pair(_strKey, img));

	p_converter->Release();		// �̹��� ��ȯ ��ü ����
	p_frame->Release();			// �׸����Ͽ� �ִ� �̹����� �����ϱ� ���� ����� ��ü ����
	p_decoder->Release();		// ������ �����ϱ� ���� ������ ��ü ����

	return img;
}

CD2DImage* CResourceManager::LoadToolD2DImage(const wstring& _strPath)
{
	if (nullptr != m_pToolImage)
	{
		delete m_pToolImage;
	}

	m_pToolImage = new CD2DImage;

	IWICBitmapDecoder* p_decoder;		// ����� �̹����� ������ ��ü
	IWICBitmapFrameDecode* p_frame;		// Ư�� �׸��� ������ ��ü
	IWICFormatConverter* p_converter;	// �̹��� ��ȯ ��ü

	// WIC�� Factory ��ü�� ����Ͽ� �̹��� ���� ������ ���� ��ü�� ����
	if (S_OK != CRenderManager::GetInst()->GetImageFactory()->CreateDecoderFromFilename(_strPath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// ������ �����ϴ� �̹��� �߿��� ù��° �̹����� �����Ѵ�.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap������ ��Ʈ���� ID2D1Bitmap. �������� ��ȯ�ϱ� ���� ��ü ����
	if (S_OK != CRenderManager::GetInst()->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ ����
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� ����
	ID2D1Bitmap* bitmap = CRenderManager::GetInst()->GetBitmap();
	if (S_OK != CRenderManager::GetInst()->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// ���������� ������ ���
	m_pToolImage->SetImage(bitmap);

	p_converter->Release();		// �̹��� ��ȯ ��ü ����
	p_frame->Release();			// �׸����Ͽ� �ִ� �̹����� �����ϱ� ���� ����� ��ü ����
	p_decoder->Release();		// ������ �����ϱ� ���� ������ ��ü ����

	return m_pToolImage;
}
