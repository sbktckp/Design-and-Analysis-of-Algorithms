CC      := gcc
CFLAGS  := -std=c17 -O2 -Wall -Wextra -Wpedantic
LDLIBS  := -lm

SRCS    := $(wildcard *.c)
BINS    := $(patsubst %.c,bin/%,$(SRCS))

all: $(BINS)

bin/%: %.c | bin
	$(CC) $(CFLAGS) -o "$@" "$<" $(LDLIBS)

bin:
	mkdir -p bin

clean:
	rm -rf bin

.PHONY: all clean
