#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

class BitArray:
    """
    BitArray: Class of getbits()
    """

    def __init__(self):
        self.SZ = 8
        self.SEVEN = 7

    def getbits(self, inArray, start, leng):
        """
        getbits: How to get some bits from a byte array.
        """
        ul = 0
        startBit = start % self.SZ
        startByte = start / self.SZ
        posInArray = int(startByte)
        dataInArray = 0
        i = 0

        pos = startBit
        #for (i = 0; i < leng; i+=1):
        for i in range(leng):
            ul <<= 1
            dataInArray = inArray[posInArray]
            ul |= (dataInArray >> (self.SEVEN - pos)) & 1
            pos += 1
            if pos >= self.SZ:
                pos = 0
                posInArray += 1
        
        return ul


def main():
    '''
    Test main
    '''
    sampleArray = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    start = 3
    length = 6

    ba = BitArray()
 
    print("Hello Bits World!")

    for v in sampleArray:
        print(f"0x{v:02X}")

    print()

    for i in range(10):
        answer = ba.getbits(sampleArray, start, length)

        print(f"Bits:{i} start:{start} len:{length} ans:{answer},0x{answer:02X}")

        start += 7
        length += 1

    print()

if __name__ == "__main__" :
    main()
