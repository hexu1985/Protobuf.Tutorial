#!/usr/bin/env python3

import sys

def zigzag32(n):
    return (n << 1) ^ (n >> 31)

def intToBin32(i):
    return bin(((1 << 32) - 1) & i)[2:].zfill(32)

def Bin32ToHex(bits):
    bits_list = []
    while len(bits) > 8:
        bits_list.append(bits[0:8])
        bits = bits[8:]
    bits_list.append(bits)
    return ["{:02x}".format(int(bits, 2)) for bits in bits_list]

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: {} n(base 10)".format(sys.argv[0]))
        print("\tprint result of zigzag32 encoding")
        sys.exit(1)

    i = int(sys.argv[1])
    print("{}: {}".format(i, Bin32ToHex(intToBin32(i))))
    print("zigzag32({})={}: {}".format(i, zigzag32(i), Bin32ToHex(intToBin32(zigzag32(i)))))
