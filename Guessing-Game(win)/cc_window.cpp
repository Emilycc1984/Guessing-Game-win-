#include "cc_window.hpp"
#include "game1.hpp"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case CC_GAME1:
	{
		switch (wParam)
		{
		case CC_DOWN:
			game->next2();
			break;
		case CC_UP:
			game->next3();
			break;
		case CC_RETURN:
			game->next1();
			break;
		case CC_UPDATE:
			game->update();
			break;
		case CC_WIN:
			cc_window::draw->begin_draw();
			cc_window::draw->draw_text(L"你赢了!", 60.0f, 60.0f, 200.0f, 100.0f);
			cc_window::draw->end_draw();
			break;
		case CC_LOSE:
			cc_window::draw->begin_draw();
			cc_window::draw->draw_text(L"你输了!", 60.0f, 60.0f, 200.0f, 100.0f);
			cc_window::draw->end_draw();
			break;
		default:
			break;
		}
		game->show();
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			game->next3();
			break;
		case VK_DOWN:
			game->next2();
			break;
		case VK_RETURN:
			PostThreadMessage(ThreadId, 0, 0, 0);
			break;
		default:
			break;
		}
		game->show();
	}
	break;
	case WM_PAINT:
	{
		cc_window::draw->begin_draw();
		game->show();
		game->update();
		cc_window::draw->end_draw();
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

static ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	//wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = (wchar_t*)"我的窗口";
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

static HWND InitInstance(HINSTANCE hInstance)
{
	//hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW((wchar_t*)"我的窗口", (wchar_t*)"测试窗口", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	return hWnd;
}

cc_draw *cc_window::draw = nullptr;

cc_window::cc_window(HINSTANCE hInst, int nCmdShow)
{
	m_hInst = hInst;
	m_CmdShow = nCmdShow;
	MyRegisterClass(hInst);
	m_hWnd = InitInstance(hInst);
}

cc_window::~cc_window()
{
	delete draw;
}

int cc_window::show()
{
	ShowWindow(m_hWnd, m_CmdShow);
	UpdateWindow(m_hWnd);

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

cc_draw *cc_window::get_draw()const
{
	if (draw == nullptr)
		draw = new cc_draw(m_hWnd);
	return draw;
}

void cc_window::post_message(UINT message, WPARAM wParam, LPARAM lParam)
{
	PostMessage(m_hWnd, message, wParam, lParam);
}