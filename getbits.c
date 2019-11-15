#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

#define IN
#define OUT

typedef unsigned char BYTE;
typedef long LONG;
typedef unsigned long ULONG;

void print(LONG l);

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

//
// len <= 32
//
LONG SignedGetBits(IN BYTE *inArray, IN int start, IN int len)
{
        LONG l = 0L;
        const char SZ = 8;
        const char SEVEN = 7;
        int startBit = start % SZ;
        int startByte = start / SZ;
        BYTE *pb = &inArray[startByte];
        int i;
        int pos;

        pos = startBit;
        for(i = 0; i < len; i++) {
                l <<= 1;
                l |= (*pb >> (SEVEN - pos++)) & 1;
                if (pos >= SZ) {
                        pos = 0;
                        pb++;
                }
        }
        if (l & (1 << (len - 1))) { /* MSB? */
                for(i = len; i < sizeof(long) * 4; i++) {
			//printf("%d(%ld): 0x%08lX\n", i, sizeof(long) * 4, l);
                        l |= (1 << i);
			//printf("%d(%ld): 0x%08lX\n", i, sizeof(long) * 4, l);
                }
        }
        return l;
}

static int count = 0;

void print(LONG l)
{
	printf("%d: %08lX=%ld\n", count++, l, l);
}

int main(int ac, char **av)
{
	BYTE testArray[8] = {
		/* 0     1     2     3     4     5     6    7 */
		0x02, 0x81,  0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0
		//0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0
	};

	LONG result;
#if 0
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
#else
	result = GetBits(testArray, 0, 11);
	print(result);
	result = SignedGetBits(testArray, 0, 11);
	print(result);

	result = GetBits(testArray, 6, 2);
	print(result);
	result = SignedGetBits(testArray, 6, 2);
	print(result);

	result = GetBits(testArray, 15, 7);
	print(result);
	result = SignedGetBits(testArray, 15, 7);
	print(result);

	result = GetBits(testArray, 15, 12);
	print(result);
	result = SignedGetBits(testArray, 15, 12);
	print(result);

	result = GetBits(testArray, 15, 15);
	print(result);
	result = SignedGetBits(testArray, 15, 15);
	print(result);
#if 0
	result = SignedGetBits(testArray, 17, 5);
	print(result);
	result = SignedGetBits(testArray, 17, 6);
	print(result);
	result = SignedGetBits(testArray, 17, 7);
	print(result);
	result = SignedGetBits(testArray, 17, 8);
	print(result);
	result = SignedGetBits(testArray, 17, 9);
	print(result);
	result = SignedGetBits(testArray, 23, 5);
	print(result);
	result = SignedGetBits(testArray, 23, 8);
	print(result);
	result = SignedGetBits(testArray, 23, 15);
	print(result);
	result = SignedGetBits(testArray, 23, 17);
	print(result);
	result = SignedGetBits(testArray, 23, 31);
	print(result);
	result = SignedGetBits(testArray, 23, 32);
	print(result);
#endif
#endif
	return 0;
}
