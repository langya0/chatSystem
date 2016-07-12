#pragma once
#include <iostream>
#include "../conf/config.h"
using namespace std;

using namespace std;
#define _SIZE_ 1024
#define _IP_ "127.0.0.1"
#define _PORT_ 8080

#ifdef __DEBUG

#define __TRACE(...) fprintf(fout,"file[%s] line[%u] func[%s]::   ",__FILE__,__LINE__,__func__);fprintf(fout,__VA_ARGS__);fprintf(fout, "\n")
#else
#define __TRACE(...);
#endif


void print_log(const char* msg,const char *fun,const int line);
