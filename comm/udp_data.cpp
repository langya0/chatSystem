#include "udp_data.h"

udp_data::udp_data()
{}
udp_data::~udp_data()
{}

void udp_data::get_nick_name(string &out)
{
	__TRACE("");
	out = nick_name;
}
void udp_data::get_school(string &out)
{
	__TRACE("");
	out = school;
}
void udp_data::get_msg(string &out)
{
	__TRACE("");
	out = msg;
}
void udp_data::get_cmd(string &out)
{
	__TRACE("");
	out = cmd;
}

void udp_data::set_nick_name(const string &in)
{
	__TRACE("");
	nick_name = in;
}
void udp_data::set_school(const string &in)
{
	__TRACE("");
	school = in;
}
void udp_data::set_msg(const string &in)
{
	__TRACE("");
	msg = in;
}
void udp_data::set_cmd(const string &in)
{
	__TRACE("");
	cmd = in;
}

void udp_data::to_string(string &out)
{
	__TRACE("");
	Json::Value val;
	val["nick_name"] = nick_name;
	val["school"]=school;
	val["msg"] = msg;
	val["cmd"] = cmd;

	my_json::serilize(val,out);
}
void udp_data::to_value(const string& in)
{
	__TRACE("");
	Json::Value val;
	
	my_json::unserilize(in,val);

	nick_name = val["nick_name"].asString() ;
	school = val["school"].asString();
	msg = val["msg"].asString();
	cmd = val["cmd"].asString();
}
