#include "my_json.h"

void my_json::serilize(Json::Value& value, string &out)
{
	__TRACE("");
	Json::StyledWriter _write;
	// Json::FastWriter _write;
	out = _write.write(value);	
}

void my_json::unserilize(const string &str,Json::Value &val)
{
	__TRACE("");
	Json::Reader read;
	read.parse(str,val,false);
}

#ifdef DEBUG_SERILIZE

int main(int argc, char const *argv[])
{
	Json::Value val;
	val["nick_name"] = "liang";
	val["school"] = "sust";
	val["msg"]="hello bit";
	val["cmd"]="None";

	string str;
	my_json::serilize(val,str);
	cout << str<<endl;
	return 0;
}
#endif