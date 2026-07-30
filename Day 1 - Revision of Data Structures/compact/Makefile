# Compact versions are deliberately loose about return values, since the whole
# point is the shortest code that works. Warnings are off here so the build
# stays quiet. The full versions one folder up are built with -Wall -Wextra
# -Wpedantic instead.

CC      := gcc
CFLAGS  := -std=c17 -O2 -w

SRCS    := $(wildcard *.c)
BINS    := $(patsubst %.c,bin/%,$(SRCS))

all: $(BINS)

bin/%: %.c | bin
	$(CC) $(CFLAGS) -o "$@" "$<"

bin:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: all clean
