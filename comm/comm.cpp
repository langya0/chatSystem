#include "comm.h"
void print_log(const char* msg,const char * const fun,int line)
{
	cout << __func__ << ":" << __LINE__ <<endl;
	cout << msg << ",[" << fun << "]," << line << endl;
}
