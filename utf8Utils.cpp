#include <iostream>
#include <stdlib.h>
#include <string.h>

int utf8len(std::string str) {
	int len = 0, byteIndex = 0;
	for (byteIndex = 0; byteIndex < str.size(); byteIndex++)
		if((str[byteIndex] & 0xc0) != 0x80)
			len++;
	return len;
}

std::string utf8substr(std::string str, int start, int desiredLength) {
	int len = 0, byteIndex = 0;
	size_t size = str.size();
	size_t startByte = -1;
	
	for (byteIndex = 0; byteIndex < size; byteIndex++) {
		if((str[byteIndex] & 0xc0) != 0x80) {
			if(len == start && startByte == -1)
				startByte = byteIndex;
			len += 1;
		}
		
		if((len - start) > desiredLength)
			break;
	}
	
	if(startByte == -1)
		startByte = 0;
	
	return str.substr(startByte, byteIndex - startByte);
}

int charPoint(std::string u) { // this expected a single unicode character (up to 4 bytes)
	int l = u.length();
	if (l < 1)
		return -1; 
	unsigned char u0 = u[0]; 
	if(u0 >= 0 && u0<=127) 
		return u0;
	if(l < 2)
		return -1; 
	unsigned char u1 = u[1]; 
	if(u0 >= 192 && u0 <= 223)
		return (u0 - 192) * 64 + (u1 - 128);
	if(u0 == 0xed && (u1 & 0xa0) == 0xa0) 
		return -1; //code points, 0xd800 to 0xdfff
		if (l < 3) 
			return -1; 
		unsigned char u2 = u[2]; 
	if (u0 >= 224 && u0 <= 239) 
		return (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
	if (l < 4) 
		return -1; 
	unsigned char u3 = u[3]; 
	if (u0 >= 240 && u0 <= 247)
		return (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
	return -1;
}

void appendUnicode(std::string &str, int c) {
	if (c < 0x80) 
		str += c;
	else if (c < 0x800) {
		str += 192 + c / 64;
		str += 128 + c % 64;
	} else if (c - 0xd800u < 0x800) {
		//error
	} else if (c < 0x10000) {
		str += 224 + c / 4096;
		str += 128 + c / 64 % 64;
		str += 128 + c % 64;
	} else if (c < 0x110000) {
		str += 240 + c / 262144;
		str += 128 + c / 4096 % 64;
		str += 128 + c / 64 % 64;
		str += 128 + c % 64;
	}
}
