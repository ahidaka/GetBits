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
	BYTE testArray[11] = {
		/* 0     1     2     3     4     5     6     7    8     9     10 */
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A
	};

	LONG result;
	int i;
	int start = 3;
	int length = 6;

	for(i = 0; i < 10; i++) {
		result = GetBits(testArray, start, length);
		printf("%d: start=%d length=%d  ", i, start, length); print(result);

		start += 7;
		length += 1;
	}
	
	return 0;
}
