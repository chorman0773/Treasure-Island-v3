#include "StringHelper.hpp"

string tokenize(string& str,string sep){
	int pos = str.find(sep);
	string ret;
	if(pos==string::npos)
		return str;
	ret = str.substr(0,pos);
	str = str.substr(pos+1,str.length()-(pos+1));
	return ret;
}

void replace(string& str,string seq,string with){
	int pos;
	while((pos=str.find(seq))!=string::npos)
		str.replace(pos,seq.length(),with);
}

int count(string str,string tok){
	int i = 0;
	for(i = 0;str.find(tok)!=string::npos;i++)
		tokenize(str,tok);
	return i;
}

string toLowerCase(string& s){
	for(int i = 0;i<s.length();i++)
		s.at(i)=tolower(s.at(i));
	return s;
}

string toUpperCase(string& s){
	for(int i = 0;i<s.length();i++)
		s.at(i)=toupper(s.at(i));
	return s;
}