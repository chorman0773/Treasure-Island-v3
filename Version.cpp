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

Version::Version():major(1),minor(0){}
Version::Version(int encoded){
	major = ((encoded/256)+1)%256;
	minor = encoded%256;
}
Version::Version(string ver){
	string mj = tokenize(ver,".");
	string mi = ver;
	major = stoi(mj);
	minor = stoi(mi);
	if(major<1||major>256||minor<0||minor>255)
		throw invalid_argument("Major must be between 1 and 256, and Minor must be between 0 and 255 (inclusive)");
}
Version::Version(int major,int minor):major(major),minor(minor){
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
Version Version::getOrigin()const{
	return Version(major,0);
}

int32_t Version::hashCode()const{
	return major*hashPrime+minor;
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
	return to_string(major)+"."+to_string(minor);
}


Version::Version(VersionConstants<minimum> _):major(MIN_MAJOR),minor(MIN_MINOR){}
Version::Version(VersionConstants<current> _):major(CURR_MAJOR),minor(CURR_MINOR){}
Version::Version(VersionConstants<currOrigin> _):major(CURR_MAJOR),minor(0){}


