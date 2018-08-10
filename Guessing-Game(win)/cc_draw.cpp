#include "cc_draw.hpp"

cc_draw::cc_draw(HWND hWnd)
{
	HRESULT hr;
	m_hWnd = hWnd;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	GetClientRect(hWnd, &m_rc);
	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(m_rc.right - m_rc.left, m_rc.bottom - m_rc.top)
		),
		&m_pRenderTarget
	);
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pWriteFactory)
	);
	m_pWriteFactory->CreateTextFormat(
		L"Arial Block",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		44,
		L"",
		&m_pTextFormat
	);
}


cc_draw::~cc_draw()
{
	m_pTextFormat->Release();
	m_pWriteFactory->Release();
	m_pBlackBrush->Release();
	m_pRenderTarget->Release();
	m_pD2DFactory->Release();
}

bool cc_draw::create_brush(float r,float g,float b)
{
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF::ColorF(r,g,b),
		&m_pBlackBrush
	);
	return true;
}

bool cc_draw::set_color(float r, float g, float b)
{
	m_pBlackBrush->SetColor(D2D1::ColorF::ColorF(r, g, b));
	return true;
}

bool cc_draw::set_textFormat(const wchar_t *fontName,float fontSize)
{
	m_pTextFormat->Release();
	m_pWriteFactory->CreateTextFormat(
		fontName,
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"",
		&m_pTextFormat
	);
	return true;
}

void cc_draw::clear(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF::ColorF(r, g, b));
}

void cc_draw::begin_draw()
{
	m_pRenderTarget->BeginDraw();
}

void cc_draw::end_draw()
{
	m_pRenderTarget->EndDraw();
}

int cc_draw::draw_text(const wchar_t *text, float left, float top, float right, float bottom)
{
	m_pRenderTarget->DrawTextA(
		text,
		wcslen(text),
		m_pTextFormat,
		D2D1::RectF(left, top, right, bottom),
		m_pBlackBrush
	);
	return wcslen(text);
}

void cc_draw::draw_line(float x1, float y1, float x2, float y2)
{
	m_pRenderTarget->DrawLine(
		D2D1::Point2F(x1, y1),
		D2D1::Point2F(x2, y2),
		m_pBlackBrush
	);
}

void cc_draw::draw_rectangle(float left,float top,float right,float bottom)
{
	m_pRenderTarget->DrawRectangle(
		D2D1::RectF(left, top, right, bottom),
		m_pBlackBrush
	);
}

void cc_draw::fill_rectangle(float left, float top, float right, float bottom)
{
	m_pRenderTarget->FillRectangle(
		D2D1::RectF(left, top, right, bottom),
		m_pBlackBrush
	);
}

void cc_draw::draw_roundedRectangle(float left, float top, float right, float bottom,float radiusX,float radiusY)
{
	m_pRenderTarget->DrawRoundedRectangle(
		D2D1::RoundedRect(
			D2D1::RectF(left,top,right,bottom),
			radiusX,
			radiusY
		),
		m_pBlackBrush
	);
}

void cc_draw::fill_roundedRectangle(float left, float top, float right, float bottom, float radiusX, float radiusY)
{
	m_pRenderTarget->FillRoundedRectangle(
		D2D1::RoundedRect(
			D2D1::RectF(left, top, right, bottom),
			radiusX,
			radiusY
		),
		m_pBlackBrush
	);
}

void cc_draw::draw_ellipse(float x, float y, float radiusX, float radiusY)
{
	m_pRenderTarget->DrawEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(x, y),
			radiusX,
			radiusY),
		m_pBlackBrush
	);
}

void cc_draw::fill_ellipse(float x, float y, float radiusX, float radiusY)
{
	m_pRenderTarget->FillEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(x, y),
			radiusX,
			radiusY),
		m_pBlackBrush
	);
}