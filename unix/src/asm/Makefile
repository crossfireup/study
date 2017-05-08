
AS = as
LD = ld

SRC = syscall.s
OBJ = $(SRC:.s=.o)

.PHONY:
	all

all: $(OBJ)
	ld -m elf32_x86_64 $< -o syscall

%.o: %.s
	$(AS) --x32 $< -o $@

.PHONY: clean

clean:
	$(RM) *.o syscall

