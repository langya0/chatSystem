#include "my_json.h"

void my_json::serilize(Json::Value& value, string &out)
{
	Json::StyledWriter _write;
	out = _write.write(value);	
}

void my_json::unserilize(string &str,Json::Value &val)
{
	Json::Reader read;
	read.parse(str,val,false);
}