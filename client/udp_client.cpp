#include "udp_client.h"

udp_client::udp_client(const string & _ip, const int &_port)
	:remote_ip(_ip)
	,port(_port)
	,sock(-1)
{
	cout << "udp_client create"<<endl;
}

udp_client::~udp_client()
{
	if(sock != -1)
	{
		close(sock);
	}
	cout << "udp_client destroy"<<endl;
}

void udp_client::init()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock==-1)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
	// listen();
}

ssize_t udp_client::udp_recv(string &out)
{
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);

	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));
	ssize_t _ret = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_ret==-1)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
	else
		out = buf;
}

ssize_t udp_client::udp_send(string &in)
{
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(remote_ip.c_str());

	socklen_t len = sizeof(remote);

	ssize_t _ret = sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&remote,len);
	if(_ret==-1)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
	return _ret;
}
