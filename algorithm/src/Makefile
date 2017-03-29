# compile c to excutable
#
#

CC = gcc
CFLAGS = -g -Wall -Wextra -m64

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(shell for o in $^; do \
		$(CC) $(CFLAGS) $$o -o $${o%.o}; \
	done;)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	$(RM) $(OBJS) $(OBJS:.o=)

