#include "../include/kernel.h"

int main(int argc, char const* argv[]) {
    (void)argc;
    (void)argv;

    char input_buffer[64];

    print_string("Enter your name: ");
    long bytes_read = read_string(input_buffer, 63);

    if (bytes_read > 0) {
        input_buffer[bytes_read] = '\0';
        print_string("Hello ");
        print_string(input_buffer);
    } else {
        print_string("Failed to read input!\n");
    }

    sys_exit(0);
    return 0;
}
