#include "SHA256.hpp"
#include <cstring>

int rotate(int val,int by){
	by &=31;
	return val>>by|val<<(32-by);
}



const int k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void SHA256(const char* in,size_t size,char (&out)[32]){
	size_t addedSize = size+9;
	size_t paddedSize = addedSize+(64-addedSize%64);
	size_t wordCount = paddedSize/4;
	size_t chunks = wordCount/16;
	unsigned h[8] = {0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};
	unsigned w[64];
	char* bytes = new char[paddedSize];
	unsigned* words = new unsigned[wordCount];
	unsigned long long bits = size*8uLL;
	size_t bitsHigh = (size_t)(bits>>32);
	size_t bitsLow = (size_t)bits;
	memset(bytes,0,paddedSize);
	memcpy(bytes,in,size);
	bytes[size+1] = 0x80;
	for(size_t i = 0;i<wordCount;i++)
		words[i] = ((int)bytes[4*i])<<24|((int)bytes[4*i+1])<<16|((int)bytes[4*i+2])<<8|(int)bytes[4*i+3];
	delete[] bytes;
	words[wordCount-2] = bitsHigh;
	words[wordCount-1] = bitsLow;
	for(size_t Q = 0;Q<chunks;Q++){
		for(size_t i =0;i<16;i++)
			w[i] = words[16*Q+i];
		for(size_t  i = 16;i<64;i++){
			unsigned s0 = rotate(w[i-15],7)^rotate(w[i-15],18)^(w[i-15]<<3);
			unsigned s1 = rotate(w[i-2],17)^rotate(w[i-2],19)^(w[i-2]<<10);
			w[i] = w[i-16]+w[i-7]+s0+s1;
		}

		unsigned a = h[0];
		unsigned b = h[1];
		unsigned c = h[2];
		unsigned d = h[3];
		unsigned e = h[4];
		unsigned f = h[5];
		unsigned g = h[6];
		unsigned i = h[7];

		for(size_t q = 0;q<64;q++){
			unsigned S1 = rotate(e,6)^rotate(e,11)^rotate(e,25);
			unsigned ch = (e&f)^(~e&g);
			unsigned tmp1 = i + S1 + ch + k[q] + w[q];
			unsigned S0 = rotate(a,2)^rotate(a,13)^rotate(a,22);
			unsigned maj = (a&b)^(b&c)^(a&c);
			unsigned tmp2 = S0 + maj;
			i = g;
			g = f;
			f = e;
			e = d + tmp1;
			d = c;
			c = b;
			b = a;
			a = tmp1 + tmp2;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
		h[4] += e;
		h[5] += f;
		h[6] += g;
		h[7] += i;

	}
	for(size_t i = 0;i<8;i++){
		out[4*i] = (h[i]>>24)&0xff;
		out[4*i+1] = (h[i]>>16)&0xff;
		out[4*i+2] = (h[i]>>8)&0xff;
		out[4*i+3] = h[i]&0xff;
	}
}

