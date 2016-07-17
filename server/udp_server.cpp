#include "udp_server.h"

udp_server::udp_server(const string &ip, const int &port)
	:ip(ip)
	,port(port)
	,sock(-1)
{
	__TRACE("udp_server create...");
}
void udp_server::old_user_del(struct sockaddr_in& client,string &out)
{
	////////ruguo cmd = q 删除用户
	udp_data data;
	data.to_value(out);
	string _cmd;
	data.get_cmd(_cmd);
	if(_cmd == "Q")
	{
		string _key_ip = inet_ntoa(client.sin_addr);
		online_user.erase(_key_ip);
	}
}

void udp_server::init()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);

	__TRACE("");

	if(sock==-1)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
}
void udp_server::add_user(struct sockaddr_in &client)
{
	__TRACE("");
	string _key_ip = inet_ntoa(client.sin_addr);////
	online_user[_key_ip] = client; //添加用户到map
}
ssize_t udp_server::udp_recv(string &out)
{
	__TRACE("");
	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	char buf[_SIZE_];
	memset(buf,'\0',sizeof(buf));

	ssize_t _ret = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	
	if(_ret==-1)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
	else
	{
		out = buf;
		pool.data_put(out);///put to datapool
			///baocun youhu xinxi 
		add_user(client);
		old_user_del(client,out);
	}
	return _ret;
}

ssize_t udp_server::udp_send(string &in,const struct sockaddr_in &client,const socklen_t &len)
{
	__TRACE("");
	ssize_t _ret = sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&client,len);
	if(_ret< 0)
	{
		print_log(strerror(errno),__func__,__LINE__);
		exit(1);
	}
	return _ret;
}

void udp_server::broadcast()
{
	__TRACE("");
	string msg;
	pool.data_get(msg);

	map<string,struct sockaddr_in>::iterator _iter = online_user.begin();
	for(;_iter!=online_user.end();++_iter)
	{
		udp_send(msg,(const struct sockaddr_in)_iter->second,sizeof(_iter->second));
	}
}

udp_server::~udp_server()
{

	if(sock != -1)
	{
		close(sock);
	}
	__TRACE("udp_server destroy...");
}
