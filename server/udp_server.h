#pragma once 
#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "comm.h"
#include "udp_data.h"
#include "data_pool.h"

using namespace std;

// #define _SIZE_ 1024
// #define _IP_ "127.0.0.1"
// #define _PORT_ 8080
class udp_server
{
public:
	udp_server();
	udp_server(const string &ip = _IP_,const int &port = _PORT_);
	~udp_server();
	void init();	
	ssize_t udp_recv(string &);
	ssize_t udp_send(string &in,const struct sockaddr_in &client,const socklen_t &len);
	void broadcast();
private:
	void add_user(struct sockaddr_in &client);
	void old_user_del(struct sockaddr_in& client,string &out);

	data_pool pool; //数据池

private:
	int sock;
	string ip;
	int  port;

	map<string,struct sockaddr_in> online_user; //在线用户


};