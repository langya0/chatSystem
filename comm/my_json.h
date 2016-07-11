#pragma once 
#include <iostream>
#include <string>
#include <string.h>
#include <json/json.h>
using namespace std;

class my_json
{
public:
	my_json();
	static void serilize(Json::Value& value, string &out);
	static void unserilize(string &str,Json::Value &val);

	~my_json();
private:
};