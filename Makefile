# CFLAGS
CC 	= gcc
AS 	= gcc
LD 	= ld
TARGET 	= c_freestanding.bin

# DIRECTORIES
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Compiling Flags
CFLAGS  = -ffreestanding -nostdinc -nostdlib -fno-builtin -Wall -Wextra -O2 -I$(INC_DIR)
ASFLAGS = -ffreestanding -nostdlib
LDFLAGS = -T linker.ld -nostdlib -no-pie

# Source and Object Files
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/sys/print.c $(SRC_DIR)/sys/string.c
ASMS    = $(SRC_DIR)/entry.s
OBJS    = $(OBJ_DIR)/entry.o $(OBJ_DIR)/main.o $(OBJ_DIR)/sys/print.o $(OBJ_DIR)/sys/string.o

# --- Build Targets ---

# Default
all: $(TARGET)

# Link
$(TARGET): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

# C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assembly files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# Clean utility
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
