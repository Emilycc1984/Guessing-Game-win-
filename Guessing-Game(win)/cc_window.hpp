#pragma once

#include <Windows.h>
#include "cc_draw.hpp"

class cc_window
{
public:
	static cc_draw *draw;

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	int m_CmdShow;

public:
	cc_window(HINSTANCE, int);
	~cc_window();

	int show();
	cc_draw *get_draw()const;
	void post_message(UINT message, WPARAM wParam, LPARAM lParam);
};

