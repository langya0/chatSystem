#include "udp_server.h"

//.ser 127.0.0.1 8080
void usage(const char * proc)
{
	cout << "Run proc as:" << proc << " [ip] [port] " << endl; 
}

void *recv_product(void* arg)
{
	udp_server *serp = (udp_server*)arg;
	bool done = false;
	string msg;
	while(!done)
	{
		__TRACE("............");
		serp->udp_recv(msg);
	}
}
void *send_comsum(void* arg)
{
	udp_server *serp = (udp_server*)arg;
	bool done = false;
	string msg;
	while(!done)
	{
		__TRACE("............");
		serp->broadcast();
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	string ip = argv[1];
	int port = atoi(argv[2]);

	string msg;
	udp_server ser(ip,port);

	__TRACE("ip%s:port%d",ip,port);

	pthread_t th1,th2;

	__TRACE("create pthread");
	pthread_create(&th1,NULL,recv_product,(void*)&ser);

	pthread_create(&th2,NULL,send_comsum,(void*)&ser);

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	__TRACE("thread done ...");

	return 0;
}
