#ifndef Random_hpp_2018_02_26_08_26
#define Random_hpp_2018_02_26_08_26
#pragma once
#include <cstdint>
#include <ctime>
#include <vector>
#include <cmath>
#include <mutex>
#include <thread>
#include <array>
typedef uint64_t seed_t;

using std::recursive_mutex;
using std::try_lock;
using std::array;

/**
	Random Number Generator Definition provided by java standard library:
	Generator location is: https://docs.oracle.com/javase/8/docs/api/java/util/Random.html
	This file follows the specification for the Random class defined by that document.
	As per the specification this class comes with 2 Warnings:
	The Random class is thread-safe, however using an instance of Random across multiple threads may have unpredictable effects.
	The Random class is not cryptographically-secure. Use the SecureRandom class instead.
	See the warnings on https://docs.oracle.com/javase/8/docs/api/java/util/Random.html for more details on these warnings
	Code implementation provided by Connor Horman.
*/

class Random{
private:
	seed_t seed;
	double nextNextGaussian;
	bool haveNextNextGaussian;	
protected:
	virtual uint32_t next(int bits);
    recursive_mutex lock;
public:
	/*
	    Constructs a Pseudorandom Number generator.
        This generate seeds the generator with a seed that is almost guarenteed to be unique from other 
        invocations of this constructor
	*/
	Random();
    /*
        Constructs a Pseudorandom Number Generator with a given seed.
        The Pseudorandom Number Generator is initialized with the seed as though it was passed to setSeed.
    */
	Random(seed_t);
    /*
        Sets the Seed of the Pseudorandom Number Generator.
        This method also has the side effect of clearing the nextNextGaussian.
        If the same sequence of methods are executed from this Pseudorandom Number generator with the same seed,
        the outputs are the same. (This guarentee also applies to Pseudorandom Number generators using the java implementation:
        java.util.Random)
    */
	virtual void setSeed(seed_t);
    
    /*
        Obtains the next int in the pseudorandom number generator
        The output of the generator is a value from 0 to 2147483647.
    */
	int nextInt();
    
    /*
        Obtains the next int in the pseudorandom number generator
        The output of this function is a value from 0 inclusive to the bound exclusive.
        If bound is negative or 0, then the method throws an exception.
    */
	int nextInt(int);
    /*
        Obtains a double from the pseudorandom number generator using Guassian/Normal distribution.
        The distribution has mean 0 and standard deviation 1. The numbers generated are extremely like to be close to 0,
        and extremely unlikely to be close to +/- Infinity.
        If the generated numbers need (approximately) uniform distribution, the nextDouble() function is more
        appropriate for use.
    */
	double nextGuassian();
    /*
        Obtains the next Long produced from this psuedorandom number generator.
        Note that because the generator only uses a 48-bit seed, the function may not
        produce all possible long values.
    */
	int64_t nextLong();
    /*
        Obtains a pseudorandom floating-point number from 0 inclusive to 1 exclusive.
        Approximately every real number(that can be represented by the float type) in this range is generated with equal probability
    */
	float nextFloat();
    /*
        Obtains a pseudorandom floating-point number from 0 inclusive to 1 exclusive
        Approximately every real number(that can be represented by the double type) in this range are generated with equal probability.
        If Normal Distribution doubles are required the nextGuassian() function is more appropriate for use.
    */
	double nextDouble();
    /*
        Obtains a number of psuedorandom bytes and fills the passed buffer with them.
    */
	virtual void nextBytes(uint8_t*,size_t);
    /*
        Fills an array with its size known at compile time with a bunch of psuedo-random bytes.
    */
	template<size_t size> void nextBytes(array<uint8_t,size>&);
	
};

template<size_t size> void Random::nextBytes(array<uint8_t,size>& bytes) {
   this->nextBytes(bytes.data(),size);
 }


#endif
