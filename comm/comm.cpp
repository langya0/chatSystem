#include "comm.h"

void print_log(const char* msg,const char * const fun,int line)
{
	__TRACE("");
	cout << msg << ",[" << fun << "]," << line << endl;
}
