#pragma once
#include <iostream>
using namespace std;

using namespace std;
#define _SIZE_ 1024
#define _IP_ "127.0.0.1"
#define _PORT_ 8080

#ifdef __DEBUG
#define __TRACE(...) fprintf(stdout, "file[%s]line[%d]func[%s]",__FILE__,__LINE__,__func__);\
fprintf(stdout,__VA_ARGS__);
fprintf(stdout, "\n");
#else
#define __TRACE(...) ;
#endif


void print_log(const char* msg,const char *fun,const int line);
