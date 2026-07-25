# Global entry point
.global _start
.global low_level_sys_write
.global low_level_sys_exit
.global low_level_sys_read

# Execution entry point
.section .text.prologue

_start:
    # 1. Align stack frame
    movq $0, %rbp
    movq %rsp, %rbp
    andq $-16, %rsp

    # 2. Call C main
    call main

# Safe loop fallback if main returns
_halt:
    movq $60, %rax     # sys_exit
    movq $0, %rdi      # status 0
    syscall

# --- PURE ASSEMBLY SYSTEM CALL FUNCTIONS ---

# C passes argument 1 (str pointer) in %rdi
# C passes argument 2 (len value)    in %rsi
low_level_sys_write:
    # We must reorganize them to match what 'syscall' expects:
    # rax = 1 (sys_write), rdi = 1 (stdout), rsi = pointer, rdx = len
    movq %rsi, %rdx    # Move length from rsi to rdx
    movq %rdi, %rsi    # Move string pointer from rdi to rsi
    movq $1, %rdi      # File descriptor 1 (stdout) into rdi
    movq $1, %rax      # Syscall number 1 (sys_write) into rax
    syscall
    ret

low_level_sys_read:
    # Reorganize registers for Linux sys_read layout:
    # rax = 0 (sys_read syscall number)
    # rdi = 0 (stdin / keyboard file descriptor)
    # rsi = buffer pointer
    # rdx = max size
    movq %rsi, %rdx    # Move max size from rsi to rdx
    movq %rdi, %rsi    # Move buffer pointer from rdi to rsi
    movq $0, %rdi      # File descriptor 0 (stdin) into rdi
    movq $0, %rax      # Syscall number 0 (sys_read) into rax
    syscall
    ret

# C passes argument 1 (status value) in %rdi
low_level_sys_exit:
    # rax = 60 (sys_exit), rdi = status
    movq $60, %rax     # Syscall number 60 (sys_exit) into rax
    syscall            # rdi already contains the status value from C!
    ret

.section .note.GNU-stack,"",@progbits
