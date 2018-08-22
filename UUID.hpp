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
	
	static UUID fromString(string);
	static UUID randomUUID();
	static UUID uuidFromNamespace(string);
	static UUID ofNow();
	constexpr static UUID nilUUID(){
		return UUID{};
	}
	constexpr UUID(uint64_t h,uint64_t l):high(h),low(l){}
	constexpr UUID():high(0),low(0){}
	UUID(string);
	UUID(const char*);
	constexpr UUID(const UUID&)=default;
	constexpr UUID(UUID&&)=default;
	UUID(const UUID&&)=delete;
	constexpr UUID& operator=(const UUID&)=default;
	constexpr UUID& operator=(UUID&&)=default;
	constexpr UUID& operator=(const UUID&&)=delete;
	constexpr uint64_t getHigh()const{
		return high;
	}
	constexpr uint64_t getLow()const{
		return low;
	}
	constexpr int32_t hashCode()const{
		return hashcode(high)*31+hashcode(low);
	}
	string toString()const;
	operator string()const;
	constexpr bool operator==(const UUID& u)const{
		return high==u.high&&low==u.low;
	}
	constexpr bool operator!=(const UUID& u)const{
		return !(*this==u);
	}
	constexpr bool operator< (const UUID& u)const{
		return high<u.high||(high==u.high&&low<u.low);
	}
	constexpr bool operator> (const UUID& u)const{
		return !(*this<=u);
	}
	constexpr bool operator<=(const UUID& u)const{
		return *this<u||*this==u;
	}
	constexpr bool operator>=(const UUID& u)const{
		return !(*this<u);
	}
	
};

ostream& operator<<(ostream&,const UUID&);
istream& operator>>(istream&,UUID&);
string  operator+(const string&,const UUID&);

constexpr int32_t hashcode(const UUID& u){
	return u.hashCode();
}

namespace std{
	template<> struct hash<UUID>{
		size_t operator()(const UUID& u){
			return u.hashCode();
		}
	};
}

#endif
