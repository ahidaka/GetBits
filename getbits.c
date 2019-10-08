#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

typedef unsigned char BYTE;
typedef unsigned long ULONG;

void print(ULONG ul);

//
// len <= 32
//
ULONG GetBits(BYTE *inArray, int start, int len)
{
	ULONG ul = 0UL;
	const char SZ = 8;
	const char SEVEN = 7;
	int startBit = start % SZ;
	int startByte = start / SZ;
	BYTE *pb = &inArray[startByte];
	int i;
	int pos;

	pos = startBit;
	for(i = 0; i < len; i++) {
		ul <<= 1;
		ul |= (*pb >> (SEVEN - pos++)) & 1;
		if (pos >= SZ) {
			pos = 0;
			pb++;
		}
	}
	return ul;
}

static int count = 0;

void print(ULONG ul)
{
	printf("%d: %08lX\n", count++, ul);
}

int main(int ac, char **av)
{
	BYTE testArray[8] = {
		/* 0     1     2     3     4     5     6    7 */
		0x02, 0x20,  0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0
		//0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0
	};

	ULONG result;

	result = GetBits(testArray, 0, 11);
	print(result);
	result = GetBits(testArray, 6, 2);
	print(result);
	result = GetBits(testArray, 15, 7);
	print(result);
	result = GetBits(testArray, 15, 12);
	print(result);
	result = GetBits(testArray, 15, 15);
	print(result);
	result = GetBits(testArray, 17, 5);
	print(result);
	result = GetBits(testArray, 17, 6);
	print(result);
	result = GetBits(testArray, 17, 7);
	print(result);
	result = GetBits(testArray, 17, 8);
	print(result);
	result = GetBits(testArray, 17, 9);
	print(result);
	result = GetBits(testArray, 23, 5);
	print(result);
	result = GetBits(testArray, 23, 8);
	print(result);
	result = GetBits(testArray, 23, 15);
	print(result);
	result = GetBits(testArray, 23, 17);
	print(result);
	result = GetBits(testArray, 23, 31);
	print(result);
	result = GetBits(testArray, 23, 32);
	print(result);

	return 0;
}
