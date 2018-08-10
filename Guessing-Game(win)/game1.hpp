#pragma once

#include <vector>
#include <Windows.h>

#define CC_GAME1 4096
#define CC_DOWN 0
#define CC_UP 1
#define CC_RETURN 2
#define CC_UPDATE 3
#define CC_WIN 4
#define CC_LOSE 5

class block;

class game1
{
private:
	std::vector<block*> m_data;
	int m_num1;
	int m_num2;

public:
	int m_life;
	int m_item1;
	int m_item2;
	int m_item3;

public:
	game1();
	~game1();

	void show();
	void next1();
	void next2();
	void next3();
	void update();
	int get_type1()const;
	int get_type2()const;
};

extern game1 *game;
extern HANDLE GameThread;
extern DWORD ThreadId;