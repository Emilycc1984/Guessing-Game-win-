#include "game1.hpp"
#include "cc_window.hpp"

#include <ctime>

class block
{
private:
	float m_X;
	float m_Y;
	int m_type;

public:
	bool m_select;

public:
	block(float x,float y)
	{
		m_X = x;
		m_Y = y;
		m_type = rand() % 3;
		m_select = false;
	}

	~block()
	{

	}

	void show()
	{
		cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
		cc_window::draw->fill_rectangle(m_X, m_Y, m_X + 60.0f, m_Y + 60.0f);
		cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
		cc_window::draw->draw_rectangle(m_X, m_Y, m_X + 60.0f, m_Y + 60.0f);
		if (m_type == 0)
		{
			cc_window::draw->draw_text(L"剪刀", m_X + 4.0f, m_Y + 10.0f, m_X + 56.0f, m_Y + 50.0f);
		}
		if (m_type == 1)
		{
			cc_window::draw->draw_text(L"石头", m_X + 4.0f, m_Y + 10.0f, m_X + 56.0f, m_Y + 50.0f);
		}
		if (m_type == 2)
		{
			cc_window::draw->draw_text(L"布", m_X + 14.0f, m_Y + 10.0f, m_X + 46.0f, m_Y + 50.0f);
		}
	}

	void select_block()
	{
		cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
		cc_window::draw->fill_rectangle(m_X, m_Y, m_X + 60.0f, m_Y + 60.0f);
		cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
		if (m_type == 0)
		{
			cc_window::draw->draw_text(L"剪刀", m_X + 4.0f, m_Y + 10.0f, m_X + 56.0f, m_Y + 50.0f);
		}
		if (m_type == 1)
		{
			cc_window::draw->draw_text(L"石头", m_X + 4.0f, m_Y + 10.0f, m_X + 56.0f, m_Y + 50.0f);
		}
		if (m_type == 2)
		{
			cc_window::draw->draw_text(L"布", m_X + 14.0f, m_Y + 10.0f, m_X + 46.0f, m_Y + 50.0f);
		}
	}

	int get_block_type()const
	{
		return m_type;
	}

	void set_block_type(int type)
	{
		m_type = type;
	}
};

game1::game1()
{
	srand((unsigned int)time(NULL));
	cc_window::draw->set_textFormat(L"宋体", 25);
	m_num1 = 0;
	m_num2 = 300000;
	m_life = 15;
	m_item1 = 5;
	m_item2 = 5;
	m_item3 = 5;

	m_data.push_back(new block(60.0f*0.0f, 60.0f*0.0f));
	m_data.push_back(new block(60.0f*1.0f, 60.0f*0.0f));
	m_data.push_back(new block(60.0f*2.0f, 60.0f*0.0f));
	m_data.push_back(new block(60.0f*3.0f, 60.0f*0.0f));
	m_data.push_back(new block(60.0f*4.0f, 60.0f*0.0f));
	m_data.push_back(new block(60.0f*5.0f, 60.0f*0.0f));

	m_data.push_back(new block(60.0f*5.0f, 60.0f*1.0f));
	m_data.push_back(new block(60.0f*5.0f, 60.0f*2.0f));
	m_data.push_back(new block(60.0f*5.0f, 60.0f*3.0f));

	m_data.push_back(new block(60.0f*5.0f, 60.0f*4.0f));
	m_data.push_back(new block(60.0f*4.0f, 60.0f*4.0f));
	m_data.push_back(new block(60.0f*3.0f, 60.0f*4.0f));
	m_data.push_back(new block(60.0f*2.0f, 60.0f*4.0f));
	m_data.push_back(new block(60.0f*1.0f, 60.0f*4.0f));
	m_data.push_back(new block(60.0f*0.0f, 60.0f*4.0f));

	m_data.push_back(new block(60.0f*0.0f, 60.0f*3.0f));
	m_data.push_back(new block(60.0f*0.0f, 60.0f*2.0f));
	m_data.push_back(new block(60.0f*0.0f, 60.0f*1.0f));

	m_data.push_back(new block(60.0f*6.5f, 60.0f*1.5f));
	m_data.push_back(new block(60.0f*6.5f, 60.0f*2.6f));
	m_data.push_back(new block(60.0f*6.5f, 60.0f*3.7f));

	m_data[18]->set_block_type(0);
	m_data[19]->set_block_type(1);
	m_data[20]->set_block_type(2);

	m_data[0]->m_select = true;
	m_data[18]->m_select = true;
}


game1::~game1()
{
	for (unsigned int i = 0; i < m_data.size(); i++)
	{
		delete m_data[i];
	}
}

void game1::show()
{
	for (unsigned int i = 0; i < m_data.size(); i++)
	{
		if (m_data[i]->m_select == true)
			m_data[i]->select_block();
		else if (m_data[i]->m_select == false)
			m_data[i]->show();
	}
}

void game1::update()
{
	wchar_t s[64];
	cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
	cc_window::draw->fill_rectangle(60.0f*6.5f, 60.0f*0.5f, 60.0f*10.0f, 60.0f*1.5f);
	cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
	swprintf_s(s, L"对方剩下%d张牌", m_life);
	cc_window::draw->draw_text(s, 60.0f*6.5f, 60.0f*0.5f, 60.0f*10.0f, 60.0f*1.5f);

	cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
	cc_window::draw->fill_rectangle(60.0f*7.7f, 60.0f*1.7f, 60.0f*10.0f, 60.0f*2.5f);
	cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
	swprintf_s(s, L"X%d", m_item1);
	cc_window::draw->draw_text(s, 60.0f*7.7f, 60.0f*1.7f, 60.0f*10.0f, 60.0f*2.0f);

	cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
	cc_window::draw->fill_rectangle(60.0f*7.7f, 60.0f*2.8f, 60.0f*10.0f, 60.0f*3.6f);
	cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
	swprintf_s(s, L"X%d", m_item2);
	cc_window::draw->draw_text(s, 60.0f*7.7f, 60.0f*2.8f, 60.0f*10.0f, 60.0f*3.1f);

	cc_window::draw->set_color(0.0f, 0.0f, 0.0f);
	cc_window::draw->fill_rectangle(60.0f*7.7f, 60.0f*3.9f, 60.0f*10.0f, 60.0f*4.8f);
	cc_window::draw->set_color(255.0f, 255.0f, 255.0f);
	swprintf_s(s, L"X%d", m_item3);
	cc_window::draw->draw_text(s, 60.0f*7.7f, 60.0f*3.9f, 60.0f*10.0f, 60.0f*4.3f);
}

void game1::next1()
{
	m_data[m_num1 % 18]->m_select = false;
	m_num1++;
	m_data[m_num1 % 18]->m_select = true;
}

void game1::next2()
{
	m_data[m_num2 % 3 + 18]->m_select = false;
	m_num2++;
	m_data[m_num2 % 3 + 18]->m_select = true;
}

void game1::next3()
{
	m_data[m_num2 % 3 + 18]->m_select = false;
	m_num2--;
	m_data[m_num2 % 3 + 18]->m_select = true;
}

int game1::get_type1()const
{
	for (unsigned int i = 18; i < 21; i++)
	{
		if (m_data[i]->m_select)
			return m_data[i]->get_block_type();
	}
	return -1;
}

int game1::get_type2()const
{
	for (unsigned int i = 0; i < 18; i++)
	{
		if (m_data[i]->m_select)
			return m_data[i]->get_block_type();
	}
	return -1;
}