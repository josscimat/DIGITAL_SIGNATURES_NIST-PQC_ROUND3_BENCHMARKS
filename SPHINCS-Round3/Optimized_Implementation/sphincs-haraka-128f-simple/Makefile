LDLIBS=-lcrypto
CC = /usr/bin/gcc
CFLAGS = -Wall -Wextra -Wpedantic -O3 -w -march=native -fomit-frame-pointer -flto

THASH = simple

SOURCES =          hash_haraka.c hash_harakax4.c thash_haraka_$(THASH).c thash_haraka_$(THASH)x4.c address.c rng.c wots.c utils.c utilsx4.c fors.c sign.c haraka.c
HEADERS = params.h hash.h        hashx4.h        thash.h               thashx4.h               address.h rng.h wots.h utils.h utilsx4.h fors.h api.h haraka.h harakax4.h

DET_SOURCES = $(SOURCES:rng.%=rng.%)
DET_HEADERS = $(HEADERS:rng.%=rng.%)

.PHONY: benchmarks

default: benchmarks

all: benchmarks

benchmarks: benchmarks.c $(DET_SOURCES) $(DET_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(DET_SOURCES) $< -lcrypto

clean:
	-$(RM) benchmarks
