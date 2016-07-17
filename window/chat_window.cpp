#include "chat_window.h"

// LINES  COLS

void chat_window::get_str(WINDOW* win,string &out)
{
	char buf[_SIZE_];
	memset(buf,'0',sizeof(buf));
	wgetnstr(win,buf,sizeof(buf)-1);

	out = buf;
}

void chat_window::put_string(WINDOW*win,int y,int x, string&str)
{
	mvwaddstr(win,y,x,str.c_str());
}

void chat_window::clear_win_line(WINDOW*win,int begin_y,int nums)
{
	while(nums-->0)
	{
		wmove(win,begin_y+nums,1);
		wclrtoeol(win);
	}
}

///////////////互斥锁保证刷新。
void chat_window::flush_window(WINDOW *win)
{
	sem_wait(&sock);
	box(win,0,0);//划线
	wrefresh(win);//刷新出来
	sem_post(&sock);
}

void chat_window::create_header()
{
	int y =0;
	int x = 0;
	int h = LINES/5;
	int w = COLS;
	header = newwin(h,w,y,x);
}
void chat_window::create_output()
{
	int y =LINES/5;
	int x = 0;
	int h = LINES*3/5;
	int w = COLS*3/4;
	output = newwin(h,w,y,x);
}
void chat_window::create_flist()
{
	int y = LINES/5;
	int x = COLS*3/4;
	int h = LINES*3/5;
	int w = COLS/4;
	flist = newwin(h,w,y,x);
}
void chat_window::create_input()
{
	int y = LINES*4/5;
	int x = 0;
	int h = LINES/5;
	int w = COLS;
	input = newwin(h,w,y,x);
}

chat_window::chat_window()
{
	sem_init(&sock,0,1);
	initscr();
	curs_set(0);
}

chat_window::~chat_window()
{
	delwin(header);
	delwin(flist);
	delwin(input);
	delwin(output);
	endwin();
}

#ifdef Debug

int main(int argc, char const *argv[])
{
	/* code */
	chat_window win;
	win.create_header();
	win.flush_window(win.header);

	string head_line = "Welcome bit-teach";

	int max_y;
	int max_x;

	getmaxyx(win.header,max_y,max_x);

	int index = max_x/3;

	// wmove(win,2,2);
	// wclrtoeol(win)

	while(1)
	{
		win.put_string(win.header,max_y/2,index,head_line);
		if(index >max_x*2/3)
		{
			index = max_x/3;
		}
		usleep(500000);
		win.flush_window(win.header);
		win.clear_win_line(win.header,max_y/2,1);

		index++;
	}

	return 0;
}

#endif