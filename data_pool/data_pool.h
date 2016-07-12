#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>

using namespace std;

class data_pool
{
public:
	data_pool(int _size = 128);
	~data_pool();
	///
	void data_get(string&);

	void data_put(const string&);

private:
	sem_t blank_sem;
	int index_pro;//生产下标
	int index_com;//消费下标

	int cap;//rongliang

	sem_t data_sem;
	std::vector<string> pool;
};