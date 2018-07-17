/*
 * Version.hpp
 * Class for Version Management.
 * Versions are comparable and Hashable. 
 *  Created on: Apr 4, 2018
 *      Author: Connor Horman
 */

#ifndef __VERSION_HPP__18_04_04_11_12_42
#define __VERSION_HPP__18_04_04_11_12_42
#include <string>
#include <iostream>
#include "Hash.hpp"

#define VERSION_CONSTEXPR constexpr
#define VERISON_DELETE =delete
#define VERSION_DEFAULT =default;

#ifdef _MSC_VER
#if _MSC_VER < 1800
#define VERSION_CONSTEXPR inline
#define VERSION_CONSTEXPR_DISABLED
#define VERSION_DELETE
#define VERSION_DEFAULT {}
#endif
#endif

#undef major 
#undef minor

using std::string;
using std::istream;
using std::ostream;




template<typename group> struct VersionConstants{
private:
	VersionConstants()VERISON_DELETE;
	VersionConstants(const VersionConstants&)VERSION_DELETE;
	VersionConstants(VersionConstants&&)VERSION_DELETE;
	VersionConstants& operator=(const VersionConstants&)VERSION_DELETE;
	VersionConstants& operator=(VersionConstants&&)VERSION_DELETE;
};

template<typename group,typename=typename std::conditional<false,decltype(group::major),decltype(group::minor)>
	struct VersionConstants<group,target>{
	public:
		VERSION_CONSTEXPR VersionConstants()VERSION_DEFAULT
		VERSION_CONSTEXPR VersionConstants(const VersionConstants&)VERSION_DEFAULT
		VERSION_CONSTEXPR VersionConstants(VersionConstants&&)VERSION_DEFAULT
		VERSION_CONSTEXPR VersionConstants& operator=(const VersionConstants&)VERSION_DEFAULT
		VERSION_CONSTEXPR VersionConstants& operator=(VersionConstants&&)VERSION_DEFAULT
		VERSION_CONSTEXPR VersionConstants(group){}

	};

/*
 * Represents a version of the code.
 * This specification only defines the Major and Minor parts of the version and is encoded
 * using The Sentry Version Encoding.
 * This class also provides utilities for obtaining versions from strings, and from a given
 * major and minor, as well as reading and writing to Data Streams (and text streams).
 * The Version class provides both the read from (istream >>) and the write to (ostream <<) operators
 * To write in string form.
 */
class Version{
private:
	unsigned char major;
	unsigned char minor;
public:
	/*
	 * Constructs an unknown (null) version.
	 * The default Version produced is 1.0
	 */
	VERSION_CONSTEXPR Version():major(0),minor(0){

	}
	/*
	 * Obtains a version given in an encoded form (Ex. 0x0000).
	 * This follows the sentry format for encoding versions (2-bytes BE, High-byte is Major version -1, Low-byte is minor version)
	 * This Constructor should be used only when you are dealing with Embedded and Encoded Version constants
	 */
 	VERSION_CONSTEXPR Version(int encoded):major(encoded>>8),minor(encoded){}
	/*
	 * Parses a given string in the form <Mj>.<mi> and produces a version given those 2 inputs.
	 * Both Mj and mi must be valid integers, with Mj being between 1 and 256 and Mi being between 0 and 255
	 */
	Version(string);
	/*
	 * Obtains a version based on a given Major and minor version.
	 * Major must be between 1 and 256 and minor must be between 0 and 255
	 */
	VERSION_CONSTEXPR Version(int maj,int min):major(maj-1),minor(min){}
	
	template<typename group> VERSION_CONSTEXPR Version(VersionConstants<group>):
	major(group::major-1),minor(group::minor){

	}
	
	/*
	 * Gets the major version, ranging from 1 to 256
	 */
	int getMajor()const;
	/*
	 * Gets the minor version, ranging from 0 to 255
	 */
	int getMinor()const;
	/*
	 * Returns the version in encoded form.
	 * The resultant value is 2-bytes consisting of major-1<<8|minor.
	 */
	int getEncoded()const;
	/*
	 * Obtains the Origin of this Version. The origin of a Version is equal to the Version
	 * that has the same Major version, but a minor version of 0.
	 */
	VERSION_CONSTEXPR Version getOrigin()const{
		return Version(int(major)+1,0);
	}
	/*
	 * Returns this Version as a string.
	 * The Resultant String is in the form <major>.<minor>
	 */
	string toString()const;
	/*
	 * Computes the hashcode of this Version.
	 * This is effectively major*31+minor
	 */
	VERSION_CONSTEXPR int32_t hashCode()const{
		return int(major)*31+int(minor);
	}
	/*
	 * Compares this version with annother. A Version is the same if its Major version and
	 * Minor version are exactly the same
	 */
	bool operator==(const Version&)const;
	/*
	 * Compares this version with another. A Version is less-than another if its major version is less
	 * than the other version's major version, or they share the same origin, and the first has a lower minor version
	 */
	bool operator<(const Version&)const;
	/*
	 * Compares this version with another. A Version is Greater-than another if its major version is greater than
	 * the other versions' major version, or they share the same origin, and the first version has a greater minor version
	 */
	bool operator>(const Version&)const;
	/*
	 * Compound Comparison <=
	 */
	bool operator<=(const Version&)const;
	/*
	 * Compound Comparison >=
	 */
	bool operator>=(const Version&)const;
};

/*
 * Reads a version from a text stream.
 * The input text is assumed to be in the form <Mj>.<mi>
 * This is effectively the same as reading a string from the stream,
 * and Constructing the associated version.
 *
 */
istream& operator>>(istream&,Version&);
/*
 * Writes this string to a text stream.
 * The output text is will be in the fomr <Mj>.<mi>
 * This is effecitvely the same as writing that version's toString()
 */
ostream& operator<<(ostream&,const Version&);



int32_t hashcode(Version v){
	return v.hashCode();
}

#endif /* __VERSION_HPP__18_04_04_11_12_42 */
