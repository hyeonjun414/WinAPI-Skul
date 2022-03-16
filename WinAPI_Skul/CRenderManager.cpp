#include "pch.h"
#include "CRenderManager.h"
#include "CD2DImage.h"

CRenderManager::CRenderManager()
{
	m_pFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pWriteFactory = nullptr;
	m_pImageFactory = nullptr;
	m_pBitmap = nullptr;
	m_pTextFormat = nullptr;
}

CRenderManager::~CRenderManager()
{
	if (nullptr != m_pRenderTarget)
	{
		m_pRenderTarget->Release();
	}
}

void CRenderManager::Init()
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	// D2D1Factory ����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	
	m_pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, SizeU(rc.right, rc.bottom),
			D2D1_PRESENT_OPTIONS::D2D1_PRESENT_OPTIONS_IMMEDIATELY ),
		&m_pRenderTarget);

	// �귯�� ����
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), & m_pBrush);

	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target�� ����
	// WICImagingFactory ����
	if (S_OK == CoInitialize(nullptr))
	{

	}
	if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)))
	{

	}
	if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)))
	{

	}
}

void CRenderManager::RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float _alpha = 1.0)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	if (nullptr != img)
	{
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	}
}

void CRenderManager::RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float _alpha)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	if (nullptr != img)
	{
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}
}

void CRenderManager::RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float _alpha)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));

	if (nullptr != img)
	{
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
}

void CRenderManager::RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize, COLORREF color)
{
	m_pWriteFactory->CreateTextFormat(
		L"����",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"ko",
		&m_pTextFormat);

	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	
	m_pBrush->SetColor(ColorF(red / 255.f, green / 255.0f, blue / 255.0f));
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT)str.size(), m_pTextFormat,
		D2D1::RectF(dstX, dstY, dstW, dstH), m_pBrush);
}

void CRenderManager::RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(ColorF(red / 255.f, green / 255.0f, blue / 255.0f));
	m_pRenderTarget->DrawRectangle(m_imgRect, m_pBrush);
}

void CRenderManager::RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(ColorF(red / 255.f, green / 255.0f, blue / 255.0f));
	m_pRenderTarget->FillRectangle(m_imgRect, m_pBrush);
}

void CRenderManager::RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(ColorF(red / 255.f, green / 255.0f, blue / 255.0f));
	m_pRenderTarget->DrawEllipse(m_imgRect, m_pBrush);
}

void CRenderManager::RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;

	m_pBrush->SetColor(ColorF(red / 255.f, green / 255.0f, blue / 255.0f));
	m_pRenderTarget->FillEllipse(m_imgRect, m_pBrush);
}

ID2D1Bitmap* CRenderManager::GetBitmap()
{
	return m_pBitmap;
}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
{
	return m_pRenderTarget;
}

IWICImagingFactory* CRenderManager::GetImageFactory()
{
	return m_pImageFactory;
}

IDWriteFactory* CRenderManager::GetWriteFactory()
{
	return m_pWriteFactory;
}

ID2D1Factory* CRenderManager::GetFactory()
{
	return m_pFactory;
}
