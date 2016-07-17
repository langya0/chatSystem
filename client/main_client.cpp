#include <strstream>
#include "udp_client.h"
#include "udp_data.h"
#include "../window/chat_window.h"

chat_window *win_p = NULL;
//全局，便于4各线程共同访问
string nick_name;
string school;

string cmd = "None";


void *draw_header(void *arg)
{
	__TRACE("");

	udp_client *cli_p = (udp_client*)arg;//client
	win_p->create_header(); //画线。在内存中

	__TRACE("");

	win_p->flush_window(win_p->header);//内存中刷新到显示屏

	int max_y;
	int max_x;

	getmaxyx(win_p->header,max_y,max_x);//获取窗口大小

	string head_line = "hello world";

	int index = 1;

	while(1)
	{
		__TRACE("");
		win_p->put_string(win_p->header,max_y/2,index++,head_line);		
		__TRACE("");
		if(index >=max_x*3/4)
			index = 1;

		win_p->flush_window(win_p->header);
		usleep(500000);
		win_p->clear_win_line(win_p->header,max_y/2,1);
	}	
}

void* draw_flist(void* arg)
{
	udp_client *cli_p = (udp_client*)arg ;
	win_p->create_flist();
	win_p->flush_window(win_p->flist);
	
	int max_x = 0;
	int max_y = 0;
	getmaxyx(win_p->flist, max_y, max_x);
	
	int num =0;
	int index = 0;
	while(1)
	{
		int fnums = cli_p->flist.size(); //用户数
		int page = max_y - 3;	//每一页显示的数
		int pages = fnums/page+1;//一共多少页
		int last_page = fnums%page;

		int i = 0;
		for ( ; num < pages ; ++num) 	//每一页输出
		{
			for(i = 0; i < page && i < fnums; ++i)	//从上到下输出用户
			{
				if (num ==  last_page-1)
				{
					int k = index;
					int line = 1;
					for(; k < fnums; ++k)
					{
						// cout << "flist [k]:" <<cli_p->flist[k]<<endl;
						win_p->put_string(win_p->flist, line++ , 1 ,cli_p->flist[k]);
						win_p->flush_window(win_p->flist);
					}

					break;
				}
				else
				{
					index = num*page + i;
					win_p->put_string(win_p->flist, i+1 , 1 ,cli_p->flist[index]);
					win_p->flush_window(win_p->flist);
				}
			}

			break;
		}

		std::string str_num;
		std::string str_total;
		std::strstream ss;
		std::strstream ss1;
		ss<<num;
		ss>>str_num;
		ss1<<pages;
		ss1>>str_total;

		std::string str_page;
		str_page = str_num;
		str_page += "/";
		str_page += str_total;


		win_p->put_string(win_p->flist, max_y-2 , max_x/2 ,str_page);
		win_p->flush_window(win_p->flist);

		sleep(1);
	}
}
void *draw_output(void *arg)
{
	__TRACE("");
	udp_client *cli_p = (udp_client*)arg;
	win_p->create_output();
	win_p->flush_window(win_p->output);

	__TRACE("");
	string recv_str;
	udp_data data;

	string nn;
	string sc;
	string cmd;
	string msg;

	string flist_str;
	int index = 1;

	int max_y, max_x;
	getmaxyx(win_p->output,max_y,max_x);

	while(1)
	{
		__TRACE("");
		cli_p->udp_recv(recv_str); 	//接受服务器广播

		//反序列化过程
		data.to_value(recv_str);
		data.get_nick_name(nn);
		data.get_school(sc);
		data.get_cmd(cmd);
		data.get_msg(msg);

		//数据提取
		string win_str = nn;
		win_str+="-";
		win_str+=sc;

		flist_str = win_str;

		win_str+="# ";
		win_str+=msg;

		if(cmd != "Q")
			cli_p->add_flist(flist_str);
		else	
			cli_p->del_flist(flist_str);

		win_p->put_string(win_p->output,index++,3,win_str);

		win_p->flush_window(win_p->output);
		if(index >= max_y-1)
		{	
			win_p->flush_window(win_p->output);
			sleep(1);
			index = 1;///add other code

			win_p->clear_win_line(win_p->output,1,max_y-1);
		}
	}	
}

void *draw_input(void *arg)
{
	udp_client *cli_p = (udp_client*)arg;
	win_p->create_input();
	win_p->flush_window(win_p->input);

	string cmd_line = "Please Enter# ";
	string win_str;

	string send_str;

	///xuliehua
	udp_data data;

	while(1)
	{
		win_p->put_string(win_p->input,1,1,cmd_line);//提示符投递
		win_p->flush_window(win_p->input);
		win_p->get_str(win_p->input,win_str);
		win_p->clear_win_line(win_p->input,1,1);

		if(win_str == "quit"||win_str == "q")
			cmd = "Q";
		// sleep(3);

		data.set_nick_name(nick_name);
		data.set_school(school);
		data.set_cmd(cmd);
		data.set_msg(win_str);
		data.to_string(send_str);
		
		cli_p->udp_send(send_str);
		if(cmd == "Q")
		{
			_exit(0);
		}
		usleep(500000);
	}	
	return	NULL;
}


void usage(const char * proc)
{
	cout << "Run proc as:" << proc << " [remote_ip] [remote_port] " << endl; 
}

	
int main(int argc, const char * argv[])
{
	__TRACE("");
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	string ip = argv[1];
	int port = atoi(argv[2]);

	cout << "Please Enter your nick_name# ";
	fflush(stdout);
	cin>> nick_name;
	cout << "Please Enter your school# ";
	fflush(stdout);
	cin>> school;

	udp_client _cli(ip,port);//创建客户端sock
	_cli.init();

	chat_window win;//窗口界面
	
	win_p = &win;

	////////////
	pthread_t header, output,flist,input;

	pthread_create(&header,NULL,draw_header,(void*)&_cli);
	pthread_create(&output,NULL,draw_output,(void*)&_cli);
	pthread_create(&flist,NULL,draw_flist,(void*)&_cli);
	pthread_create(&input,NULL,draw_input,(void*)&_cli);

	pthread_join(header,NULL);
	pthread_join(output,NULL);
	pthread_join(flist,NULL);
	pthread_join(input,NULL);
}
