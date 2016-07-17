#include "udp_client.h"

void udp_client::del_flist(string &old_user)
{
	vector<string>::iterator it = flist.begin();
	for(;it!=flist.end();++it)
	{
		if(*it==old_user)
		{
			it = flist.erase(it);
			break;
		}
		else
			++it;
	}
}	

void udp_client::add_flist(string &user)
{
	std::vector<string>::iterator it=flist.begin();
	for(;it!=flist.end();++it)
	{
		if(*it==user)
			break;
	}
	if(it==flist.end())
	{
		flist.push_back(user);
	}
}

udp_client::udp_client(const string & _ip, const int &_port)
	:remote_ip(_ip)
	,port(_port)
	,sock(-1)
{
	__TRACE("udp_client create");
}

udp_client::~udp_client()
{
	__TRACE("");
	if(sock != -1)
	{
		close(sock);
	}
	cout << "udp_client destroy"<<endl;
}

void udp_client::init()
{
	__TRACE("");
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
	__TRACE("");
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
	__TRACE("");
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
