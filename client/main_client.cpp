#include "udp_client.h"

void usage(const char * proc)
{
	cout << "Run proc as:" << proc << " [remote_ip] [remote_port] " << endl; 
}

int main(int argc, const char * argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	string ip = argv[1];

	int port = atoi(argv[2]);

	udp_client _cli(ip,port);
	_cli.init();

	char buf[_SIZE_];
	while(1)
	{
		cout << "Please Enter#"<<endl;
		memset(buf,'\0',sizeof(buf));
		ssize_t _s = read(0,buf,sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s -1] = '\0';
		}

		string out = buf;
		_cli.udp_send(out);
		out = "";
		
		_cli.udp_recv(out);
		cout << "server echo#" << out << endl;
	}
}