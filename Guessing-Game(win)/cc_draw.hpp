#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

class cc_draw
{
private:
	ID2D1Factory *m_pD2DFactory;
	ID2D1HwndRenderTarget *m_pRenderTarget;
	ID2D1SolidColorBrush *m_pBlackBrush;
	IDWriteFactory *m_pWriteFactory;
	IDWriteTextFormat *m_pTextFormat;
	RECT m_rc;
	HWND m_hWnd;
	friend class cc_window;

protected:
	cc_draw(HWND);

public:
	~cc_draw();

	bool create_brush(float r, float g, float b);
	bool set_color(float r, float g, float b);
	bool set_textFormat(const wchar_t *fontName, float fontSize);
	void clear(float r, float g, float b);
	void begin_draw();
	void end_draw();
	int draw_text(const wchar_t *text, float left, float top, float right, float bottom);
	void draw_line(float x1, float y1, float x2, float y2);
	void draw_rectangle(float left, float top, float right, float bottom);
	void fill_rectangle(float left, float top, float right, float bottom);
	void draw_roundedRectangle(float left, float top, float right, float bottom, float radiusX, float radiusY);
	void fill_roundedRectangle(float left, float top, float right, float bottom, float radiusX, float radiusY);
	void draw_ellipse(float x, float y, float radiusX, float radiusY);
	void fill_ellipse(float x, float y, float radiusX, float radiusY);
};

