LDLIBS=-lcrypto
CC = /usr/bin/gcc
CFLAGS = -Wall -Wextra -Wpedantic -O3 -w -march=native -fomit-frame-pointer -flto

THASH = simple

SOURCES =          hash_shake256.c hash_shake256x4.c thash_shake256_$(THASH).c thash_shake256_$(THASH)x4.c address.c rng.c wots.c utils.c utilsx4.c fors.c sign.c fips202.c fips202x4.c keccak4x/KeccakP-1600-times4-SIMD256.o
HEADERS = params.h hash.h          hashx4.h          thash.h                 thashx4.h                 address.h rng.h wots.h utils.h utilsx4.h fors.h api.h fips202.h fips202x4.h

DET_SOURCES = $(SOURCES:rng.%=rng.%)
DET_HEADERS = $(HEADERS:rng.%=rng.%)

.PHONY: benchmarks

default: benchmarks

all: benchmarks

benchmarks: benchmarks.c $(DET_SOURCES) $(DET_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(DET_SOURCES) $< -lcrypto

keccak4x/KeccakP-1600-times4-SIMD256.o: keccak4x/align.h \
										keccak4x/brg_endian.h \
										keccak4x/KeccakP-1600-times4-SIMD256.c \
										keccak4x/KeccakP-1600-times4-SnP.h \
										keccak4x/KeccakP-1600-unrolling.macros \
										keccak4x/SIMD256-config.h
	$(CC) $(CFLAGS) -c keccak4x/KeccakP-1600-times4-SIMD256.c -o $@

clean:
	-$(RM) keccak4x/KeccakP-1600-times4-SIMD256.o
	-$(RM) benchmarks
