LOCAL=/usr/local

HEAD=$(wildcard include/*.h)
SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)

CC=gcc
LDFLAGS=-lkeccak -lcrypto -ldl -lpthread
# CFLAGS=-Wall -O4 -mavx2 -mpclmul -mpopcnt -funroll-loops -Iinclude/ -I$(LOCAL)/include -L$(LOCAL)/lib
CFLAGS=-Wall -O4 -march=native -mtune=native -funroll-loops -Iinclude/ -I$(LOCAL)/include -L$(LOCAL)/lib -w

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
