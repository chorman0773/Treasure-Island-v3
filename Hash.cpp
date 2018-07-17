#include "Hash.hpp"
#include <array>
#include <utility>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <typeinfo>
#include <cstdint>
#include <memory>
#include <chrono>


extern const int hashPrime(31);




using std::type_info;

int32_t hashcode(const type_info& t){
	return t.hash_code();
}

int32_t Hashable::hashCode() const{
	return ::hashcode((void*)this);
}

namespace std{
	template<> class hash<Hashable>{
	public:
		typedef Hashable argument_type;
		typedef size_t result_type;
		size_t operator()(const Hashable& h)throw(){
			return h.hashCode();
		}
	};
};

