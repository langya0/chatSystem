#pragma once 
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "comm.h"
using namespace std;

class udp_client
{
public:	
	udp_client(const string & _ip = _IP_, const int &_port = _PORT_);
	ssize_t udp_recv(string &out);
	ssize_t udp_send(string &in);
	
	void add_flist(string &user);
	void del_flist(string &old_user);

	~udp_client();
	void init();

	std::vector<string> flist;
private:
	string remote_ip;
	int sock;
	int port;

};