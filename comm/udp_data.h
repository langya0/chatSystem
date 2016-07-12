#pragma once 

#include <iostream>
#include <string>

#include "my_json.h"
using namespace std;

class udp_data
{
public:
	udp_data();
	~udp_data();

	void get_nick_name(string &);
	void get_school(string &);
	void get_msg(string &);
	void get_cmd(string &);
	void set_nick_name(const string &);
	void set_school(const string &);
	void set_msg(const string &);
	void set_cmd(const string &);

	void to_string(string &);
	void to_value(const string&);
private:
	string nick_name;
	string school;
	string msg;
	string cmd;
};