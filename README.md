# sinelut
Command line Sine look-up table generator

Simple software that allows to create sine/cosine valued LUTs to be created. Poerfect for testing audio signal paths involving Digital to Analog converters.

# How to build

`gcc -o sinelut.exe -lm sinelut.c`

Nothing more, nothing less.

# Usage

This command line tool accepts quite a few parameters:

-  -n             number of array elements (**required**)
-  -a             amplitude (default - maximal amplitude for given output bit width)
-  -p             sine period expressed in number of elements
-  -s             sine starting angle (relative to period, default: one full period in output buffer)
-  -o             additional offset (added to every sample, default: 0 (zero-centered sine))
-  -b             bit width of a single array element (8 (default), 16, 32)
-  -l             number of elements per line  (0 - single line output, default: 8)

# Examples

Ex. 1: **Generate a sine array that has 100 byte elements**

Input:

`sinelut.exe -n 100`

Output:

``` 
0x00, 0x07, 0x0f, 0x17, 0x1f, 0x27, 0x2e, 0x36,
0x3d, 0x44, 0x4a, 0x50, 0x56, 0x5c, 0x61, 0x66,
0x6b, 0x6f, 0x72, 0x76, 0x78, 0x7b, 0x7c, 0x7d,
0x7e, 0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x78, 0x76,
0x72, 0x6f, 0x6b, 0x66, 0x61, 0x5c, 0x56, 0x50,
0x4a, 0x44, 0x3d, 0x36, 0x2e, 0x27, 0x1f, 0x17,
0x0f, 0x07, 0x00, 0xf9, 0xf1, 0xe9, 0xe1, 0xd9,
0xd2, 0xca, 0xc3, 0xbc, 0xb6, 0xb0, 0xaa, 0xa4,
0x9f, 0x9a, 0x95, 0x91, 0x8e, 0x8a, 0x88, 0x85,
0x84, 0x83, 0x82, 0x81, 0x82, 0x83, 0x84, 0x85,
0x88, 0x8a, 0x8e, 0x91, 0x95, 0x9a, 0x9f, 0xa4,
0xaa, 0xb0, 0xb6, 0xbc, 0xc3, 0xca, 0xd2, 0xd9,
0xe1, 0xe9, 0xf1, 0xf9
```


Ex. 2: **Generate a cosine array that has 16 16-bit elements**

Input:

`sinelut.exe -n 16 -s 4 -b 16`

Output:

```
0x7fff, 0x7640, 0x5a81, 0x30fb, 0x0000, 0xcf05, 0xa57f, 0x89c0,
0x8001, 0x89c0, 0xa57f, 0xcf05, 0x0000, 0x30fb, 0x5a81, 0x7640,
```

Ex. 3: **Generate a sine (with a single period of 8 samples and amplitude of 1000) in 64 element array that has 64 32-bit elements. Add an offset of 10 to every sample. Format the output so that it has 4 entries per line.**


Input:

`sinelut.exe -n 64 -p 8 -a 1000 -b 32 -o 10 -l 4`

Output:

```
0x0000000a, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x00000009, 0xfffffd47, 0xfffffc22, 0xfffffd47,
0x00000009, 0x000002cd, 0x000003f2, 0x000002cd,
0x0000000a, 0xfffffd47, 0xfffffc22, 0xfffffd47,
```

