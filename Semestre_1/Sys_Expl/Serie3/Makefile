# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executables
EXECUTABLES = inode_info sb_info

# Object files
OBJS_INODE_INFO = inode_info.o minix_utils.o
OBJS_SB_INFO = sb_info.o minix_utils.o

# Default target
all: $(EXECUTABLES)

# Compile inode_info
inode_info: $(OBJS_INODE_INFO)
	$(CC) $(CFLAGS) -o $@ $(OBJS_INODE_INFO)

# Compile sb_info
sb_info: $(OBJS_SB_INFO)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SB_INFO)

# Compile .c files into .o files
%.o: %.c minix.h
	$(CC) $(CFLAGS) -c $<

# Clean up build files
clean:
	rm -f $(EXECUTABLES) *.o
