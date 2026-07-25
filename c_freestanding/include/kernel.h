#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned long size_t;
typedef unsigned long uintptr_t;

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

// Boolean
typedef enum { FALSE = 0, TRUE = 1 } bool_t;

// NullPointer
#define NULL ((void*)0)

// Helper to find the number of elements in a static array.
// Division is required because sizeof() returns total size in BYTES, not
// elements. Total array bytes divided by bytes of the first element = element
// count.
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// From src/sys/string.c
size_t strlen(const char* str);
void* memset(void* dest, int ch, size_t count);
void* memcpy(void* dest, const void* src, size_t count);
int strcmp(const char* s1, const char* s2);

// From src/sys/print.c
void print_string(const char* str);
void print_char(char c);
void low_level_sys_write(const char* str, unsigned long len);
long low_level_sys_read(char* buffer, unsigned long max_size);
long read_string(char* buffer, size_t max_size);
void low_level_sys_exit(int status);
void sys_exit(int status);

#endif /* KERNEL_H */
