LOCAL=/usr/local

HEAD=$(wildcard include/*.h)
SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)

CC=gcc
LDFLAGS=-lkeccak -lcrypto -ldl -lpthread
# -march=native -mtune=native are used to inline functions of the gf2x library when PCLMULQDQ is available.
CFLAGS=-Wall -O2 -march=native -mtune=native -Iinclude/ -I$(LOCAL)/include -L$(LOCAL)/lib -w

all: benchmarks


benchmarks: $(OBJS)
	# if gf2x is enabled, the -lgf2x flag is added
	@if [ `grep -c "#define ENABLED_GF2X 1" include/arch.h` != "0" ]; then \
	    echo $(CC) $(CFLAGS) -o $@ $^ -lgf2x $(LDFLAGS);\
	    $(CC) $(CFLAGS) -o $@ $^ -lgf2x $(LDFLAGS);\
	else \
	    echo $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS);\
	    $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS);\
	fi;
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f benchmarks src/*.o *.int
