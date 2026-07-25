#include "../../include/kernel.h"
#include "kernel.h"

// Calculate the length of a null-terminated string
size_t strlen(const char* str) {
    size_t length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

// Fill a block of memory with a specific byte value
void* memset(void* dest, int ch, size_t count) {
    unsigned char* ptr = (unsigned char*)dest;

    for (size_t i = 0; i < count; i++) {
        ptr[i] = (unsigned char)ch;
    }

    return dest;
}

// Copy a block of memory from one location to another
void* memcpy(void* dest, const void* src, size_t count) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < count; i++) {
        d[i] = s[i];
    }
    return dest;
}
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return  (unsigned char)*s1 - (unsigned char)*s2;
}