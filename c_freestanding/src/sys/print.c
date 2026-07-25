#include "../../include/kernel.h"

// Adding just to remove vsc warning
#ifdef __INTELLISENSE__
void low_level_sys_write(const char* str, unsigned long len) { (void)str; (void)len; }
long low_level_sys_read(char* buffer, unsigned long max_size) { (void)buffer; (void)max_size; return 0; }
void low_level_sys_exit(int status) { (void)status; }
#endif

void print_string(const char* str) {
    size_t len = strlen(str);
    low_level_sys_write(str, len);
}

long read_string(char* buffer, size_t max_size) {
    return low_level_sys_read(buffer, max_size);
}

void sys_exit(int status) {
    low_level_sys_exit(status);
}

void print_char(char c) {
    char buf[2] = {c, '\0'};
    print_string(buf);
}
