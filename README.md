# Custom Freestanding C Project (No Standard Library)

A minimal, high-utility, freestanding C development environment configured for native **64-bit Linux (x86_64)**. This project operates completely independent of the standard C library (`libc`) and compiler-provided runtime headers. It implements its own custom memory-mapping, low-level assembly layers, and direct hardware kernel system calls (`syscall`).

## 🚀 Key Features
* **Zero Standard Library Dependencies**: Uses specialized compiler flags (`-ffreestanding`, `-nostdlib`, `-nostdinc`) to strip away default code runtimes.
* **Pure Assembly Syscall Infrastructure**: Discards standard compiler macros for direct x86_64 Application Binary Interface (ABI) register mappings via pure assembly.
* **Custom Type Blueprint (`kernel.h`)**: Implements independent baseline architectural definitions (`size_t`, fixed-width unsigned integers).
* **IDE Optimization Matrix**: Utilizes contextual macro guards (`__INTELLISENSE__`) to bypass static analysis boundaries without altering hardware binaries.

---

## 📁 Directory Structure
```text
c_freestanding/
├── include/
│   └── kernel.h            # Private substitution header for stdint/stddef/stdio
├── src/
│   ├── entry.s             # Assembly initialization vector (stack & ABI layout)
│   ├── main.c              # Upper-level freestanding logic entry
│   └── sys/
│       ├── print.c         # Hardware interaction interfaces (write, read, exit)
│       └── string.c        # Low-level string manipulation routines (strlen, strcmp)
├── obj/                    # Dynamically generated compilation artifact targets
├── Makefile                # Multi-stage automated toolchain matrix
└── linker.ld               # Memory layout script targeting 0x400000 space
```

---

## 🛠️ Toolchain System Requirements
* **Operating System**: Linux (Ubuntu 24.04 LTS native x86_64 environment verified)
* **Compiler Utility**: GCC Compiler Suite (`gcc`)
* **Linker Core**: GNU Linker (`ld`)
* **Automation**: GNU Make (`make`)

---

## ⚡ Execution and Compilation Commands

Open your terminal environment inside the project root directory and trigger these automated processes:

### 1. Compile the Binary
Wipes existing temporary storage artifacts and builds a clean binary matrix execution file:
```bash
make clean && make
```

### 2. Launch the Application
Executes the native freestanding image within your active user terminal space:
```bash
./c_freestanding.bin
```

---

## 🔍 Technical Implementation Overview

### Memory Alignment (`linker.ld`)
The program bypasses traditional random memory layouts by dictating its boundaries straight to the linker. It specifies an architecture target of `0x400000` (the formal load baseline space for Linux user-space binaries), keeping compiled operational sequences page-aligned to strict 4K hardware configurations:
```linker
ENTRY(_start)
SECTIONS {
    . = 0x400000;
    .text : ALIGN(4K) { *(.text.prologue) *(.text) }
    ...
}
```

### Stack Alignment & Global Call Entry (`entry.s`)
The assembly sequence establishes an immediate system control anchor. It overrides standard system stubs, safely establishes a 16-byte aligned 64-bit hardware stack framework (`%rsp`), executes a direct logical transition route into the C codebase layer, and catches potential instruction overflows via an explicit system exit trap structure.
```assembly
_start:
    movq \$0, %rbp
    movq %rsp, %rbp
    andq \$-16, %rsp
    call main
```
