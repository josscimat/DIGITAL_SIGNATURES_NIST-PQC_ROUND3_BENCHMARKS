CC=gcc
CFLAGS+=-g -O3 -w

SOURCES=$(filter-out randomness.c,$(wildcard *.c)) $(wildcard sha3/*.c) $(wildcard sha3/*.s)
EXECUTABLE_BENCHMARKS=benchmarks
LIBPICNIC=libpicnic.a

all: $(LIBPICNIC) $(EXECUTABLE_BENCHMARKS)

$(LIBPICNIC): $(SOURCES:.c=.o) $(SOURCES:.s=.o)
	ar rcs $@ $^

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.s.o:
	$(CC) -c $(CFLAGS) -mavx2 $< -o $@

$(EXECUTABLE_BENCHMARKS): CFLAGS+=-Wno-sign-compare -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-result -w

$(EXECUTABLE_BENCHMARKS): $(LIBPICNIC) randomness.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lcrypto -o $@

clean:
	rm -f $(wildcard *.o) $(wildcard sha3/*.o) $(LIBPICNIC) $(EXECUTABLE_BENCHMARKS)
