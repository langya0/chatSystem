#pragma once 

#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include "../comm/comm.h"
#include <semaphore.h>
#include <string.h>
using namespace std;
#include <ncurses.h>

class chat_window
{
public:
	chat_window();
	~chat_window();
	void flush_window(WINDOW *win);
	void get_str(WINDOW* win,string &out);

	void put_string(WINDOW*win,int y,int x, string&);
	void clear_win_line(WINDOW*win,int begin_y,int nums);

	void create_header();
	void create_output();
	void create_flist();
	void create_input();
// private:
public:
	WINDOW *header;
	WINDOW *output;
	WINDOW *flist;
	WINDOW *input;

	sem_t sock;
};