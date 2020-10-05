using System;

namespace GetBits_cs
{

    public class BitArray
    {
        const int SZ = 8;
        const ulong SEVEN = 7;

        public ulong GetBits(byte[] inArray, uint start, uint length)
        {
            ulong ul = 0;
            uint startBit = (uint)start % SZ;
            uint startByte = (uint)start / SZ;
            //BYTE* pb = &inArray[startByte];
            uint posInArray = startByte;
            ulong dataInArray;
            uint i;
            uint pos;

            pos = startBit;
            for (i = 0; i < length; i++)
            {
                ul <<= 1;
                dataInArray = inArray[posInArray];
                ul |= (dataInArray >> (int)(SEVEN - pos++)) & 1;
                if (pos >= SZ)
                {
                    pos = 0;
                    posInArray++;
                }
            }
            return ul;
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            byte[] sampleArray = new byte[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int i;
            uint start = 3;
            uint length = 6;
            BitArray ba = new BitArray();

            Console.WriteLine("Hello Bits World!");

            for (i = 0; i < 10; i++)
            {
                Console.Write("0x{0:X} ", sampleArray[i]);
            }
            Console.WriteLine("");

            for (i = 0; i < 10; i++)
            {
                ulong answer = ba.GetBits(sampleArray, start, length);

                Console.WriteLine("Bits i:{0} start:{1} len:{2} ans:{3},0x{3:X}",
                    i, start, length, answer);

                start += 7;
                length++;
            }
        }
    }
}
