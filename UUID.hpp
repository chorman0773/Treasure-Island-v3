#ifndef __UUID_hpp_2018_05_16_08_22
#define __UUID_hpp_2018_05_16_08_22
#include <string>
#include <cstdint>
#include "Hash.hpp"
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class UUID{
private:
	uint64_t high;
	uint64_t low;
public:
	static const UUID NIL;
	static UUID fromString(string);
	static UUID randomUUID();
	static UUID uuidFromNamespace(string);
	static UUID ofNow();
	UUID(uint64_t,uint64_t);
	UUID();
	UUID(string);
	UUID(const char*);
	uint64_t getHigh()const;
	uint64_t getLow()const;
	int32_t hashCode()const;
	string toString()const;
	operator string()const;
	bool operator==(const UUID&)const;
	bool operator!=(const UUID&)const;
	bool operator< (const UUID&)const;
	bool operator> (const UUID&)const;
	bool operator<=(const UUID&)const;
	bool operator>=(const UUID&)const;
};

ostream& operator<<(ostream&,const UUID&);
istream& operator>>(istream&,UUID&);
string  operator+(const string&,const UUID&);

int32_t hashcode(const UUID&);

#endif
