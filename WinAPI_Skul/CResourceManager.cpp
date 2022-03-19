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
	// 불러온 리소스들을 메모리 해제 시킨다.
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
	// 텍스쳐를 먼저 탐색해보고 있다면 해당 텍스쳐를 반환한다.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;


	// 불러온 텍스쳐가 없다면 불러오는 과정을 진행하고 해당 텍스쳐를 반환한다.
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

	// 텍스쳐를 찾지 못했다면 널포인트 반환
	if (iter == m_mapTex.end()) 
		return nullptr;

	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{
	// 사운드를 먼저 탐색해보고 있다면 해당 사운드를 반환한다.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound) return pSound;

	// 불러온 사운드가 없다면 불러오는 과정을 진행하고 해당 사운드를 반환한다.
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

	// 사운드를 찾지 못했다면 널포인트 반환
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
	// CD2DImage 키 값을 통해 탐색
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

	IWICBitmapDecoder* p_decoder;		// 압축된 이미지를 해제할 객체
	IWICBitmapFrameDecode* p_frame;		// 특정 그림을 선택한 객체
	IWICFormatConverter* p_converter;	// 이미지 변환 객체

	// WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
	if (S_OK != SINGLE(CRenderManager)->GetImageFactory()->CreateDecoderFromFilename(strFilePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
	if (S_OK != SINGLE(CRenderManager)->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
	ID2D1Bitmap* bitmap = SINGLE(CRenderManager)->GetBitmap();
	if (S_OK != SINGLE(CRenderManager)->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// 성공적으로 생성한 경우
	img->SetImage(bitmap);
	img->SetKey(_strKey);
	img->SetRelativePath(_strRelativePath);
	m_mapD2DImg.insert(make_pair(_strKey, img));

	p_converter->Release();		// 이미지 변환 객체 제거
	p_frame->Release();			// 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
	p_decoder->Release();		// 압축을 해제하기 위해 생성한 객체 제거

	return img;
}

CD2DImage* CResourceManager::LoadToolD2DImage(const wstring& _strPath)
{
	if (nullptr != m_pToolImage)
	{
		delete m_pToolImage;
	}

	m_pToolImage = new CD2DImage;

	IWICBitmapDecoder* p_decoder;		// 압축된 이미지를 해제할 객체
	IWICBitmapFrameDecode* p_frame;		// 특정 그림을 선택한 객체
	IWICFormatConverter* p_converter;	// 이미지 변환 객체

	// WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
	if (S_OK != CRenderManager::GetInst()->GetImageFactory()->CreateDecoderFromFilename(_strPath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
	if (S_OK != CRenderManager::GetInst()->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
	ID2D1Bitmap* bitmap = CRenderManager::GetInst()->GetBitmap();
	if (S_OK != CRenderManager::GetInst()->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// 성공적으로 생성한 경우
	m_pToolImage->SetImage(bitmap);

	p_converter->Release();		// 이미지 변환 객체 제거
	p_frame->Release();			// 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
	p_decoder->Release();		// 압축을 해제하기 위해 생성한 객체 제거

	return m_pToolImage;
}
