/*
 * Version.cpp
 *
 *  Created on: Apr 4, 2018
 *      Author: Connor Horman
 */
#include "Version.hpp"
#include "StringHelper.hpp"
#include <string>
#include <stdexcept>
#define CURR_MAJOR 1
#define CURR_MINOR 0
#define MIN_MAJOR  1
#define MIN_MINOR  0

using std::string;
using std::to_string;
using std::stoi;
using std::invalid_argument;

const extern int32_t hashPrime;


Version::Version(string ver){
	string mj = tokenize(ver,".");
	string mi = ver;
	major = stoi(mj);
	minor = stoi(mi);
	if(major<1||major>256||minor<0||minor>255)
		throw invalid_argument("Major must be between 1 and 256, and Minor must be between 0 and 255 (inclusive)");
}



int Version::getEncoded()const{
	return (major-1)*256|minor;
}
int Version::getMajor()const{
	return major;
}
int Version::getMinor()const{
	return minor;
}



bool Version::operator==(const Version& o)const{
	return major==o.major&&minor==o.minor;
}
bool Version::operator<(const Version& o)const{
	return major<o.major||(major==o.major&&minor<o.minor);
}
bool Version::operator>(const Version& o)const{
	return major>o.major||(major==o.major&&minor>o.minor);
}
bool Version::operator<=(const Version& o)const{
	return *this==o||*this<o;
}
bool Version::operator>=(const Version& o)const{
	return *this==o||*this>o;
}


ostream& operator <<(ostream& o,const Version& v){
	return o<<v.toString();
}
istream& operator >>(istream& i,Version& v){
	string s;
	i >> s;
	v = s;
	return i;
}

string Version::toString()const{
	return to_string(int(major)+1)+"."+to_string(minor);
}




