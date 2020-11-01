# Notes

## Endian-safety
Both polynomial and matrix code are not endian-safe. That is if a matrix is generated on a machine the raw bytes will be possibly read as a different matrix on a machine with different endianness. The reason for this is the code reads and writes the sequential bits in blocks of 4 or 8 bytes instead of one byte at a time to improve performance.

This may not be a very big concern considering almost any processor/operating system of this generation runs in Little Endian mode. On a big endian machine it is possible to solve this by using block sizes of 1 byte. With this change big endian machines will be interoperable essentially working like little endian.
