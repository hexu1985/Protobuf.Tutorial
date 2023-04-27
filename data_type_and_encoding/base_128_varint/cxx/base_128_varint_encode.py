#!/usr/bin/env python3

import sys

def intToBin32(i):
    return bin(((1 << 32) - 1) & i)[2:]

def base_128_varint_encode(istr):
    bits=intToBin32(int(istr))
    bits_list=[]
    while len(bits) > 7:
        bits_list.append('1'+bits[-7:])
        bits=bits[:-7]
    bits_list.append((8-len(bits))*'0'+bits) 
    return bits_list

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: {} n(base 10)".format(sys.argv[0]))
        print("\tprint result of base-128-varint encoding")
        sys.exit(1)

    bits_list = base_128_varint_encode(sys.argv[1])
    print(bits_list)
    for bits in bits_list:
        print("{:02x}".format(int(bits, 2)), end=" ")
    print()
