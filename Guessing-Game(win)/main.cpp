#include "cc_window.hpp"
#include "game1.hpp"

game1 *game;
HANDLE GameThread;
DWORD ThreadId;

static const char date[3][3] =
{
	{ 0,-1,1 },
	{ 1,0,-1 },
	{ -1,1,0 }
};

static void run_1(cc_window *win)
{
	for (int i = 0; i < 100 + rand() % 10; i++)
	{
		win->post_message(CC_GAME1, CC_RETURN, 0);
		Sleep(10);
	}
}

static void run_2(cc_window *win)
{
	for (int i = 0; i < 12; i++)
	{
		win->post_message(CC_GAME1, CC_RETURN, 0);
		Sleep(100);
	}
}

static void run_3(cc_window *win)
{
	for (int i = 0; i < 6; i++)
	{
		win->post_message(CC_GAME1, CC_RETURN, 0);
		Sleep(300);
	}
}

static void run(cc_window *win)
{
	run_1(win);
	run_2(win);
	run_3(win);
}

static DWORD WINAPI Thread(LPVOID lpParameter)
{
	cc_window *win = (cc_window*)lpParameter;
	int type1, type2;
	MSG msg;
	while (1)
	{
		GetMessage(&msg, nullptr, 0, 0);
		type1 = game->get_type1();
		if (type1 == 0 && game->m_item1 <= 0)
			continue;
		else if (type1 == 1 && game->m_item2 <= 0)
			continue;
		else if (type1 == 2 && game->m_item3 <= 0)
			continue;
		else if (game->m_life <= 0)
			continue;
		run(win);
		type2 = game->get_type2();
		switch (date[type1][type2])
		{
		case -1:
			if (type1 == 0)
				game->m_item1--;
			else if (type1 == 1)
				game->m_item2--;
			else if (type1 == 2)
				game->m_item3--;
			break;
		case 0:
			if (type1 == 0)
				game->m_item1--;
			else if (type1 == 1)
				game->m_item2--;
			else if (type1 == 2)
				game->m_item3--;
			game->m_life--;
			break;
		case 1:
			game->m_life--;
			break;
		default:
			break;
		}
		if (game->m_life <= 0)
			win->post_message(CC_GAME1, CC_WIN, 0);
		else if (game->m_item1 + game->m_item2 + game->m_item3 <= 0)
			win->post_message(CC_GAME1, CC_LOSE, 0);
		else
			win->post_message(CC_GAME1, CC_UPDATE, 0);
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	cc_window win(hInstance, nCmdShow);
	win.get_draw()->create_brush(255.0f, 255.0f, 255.0f);
	game = new game1;
	GameThread = CreateThread(nullptr, 0, Thread, &win, NULL, &ThreadId);
	return win.show();
}