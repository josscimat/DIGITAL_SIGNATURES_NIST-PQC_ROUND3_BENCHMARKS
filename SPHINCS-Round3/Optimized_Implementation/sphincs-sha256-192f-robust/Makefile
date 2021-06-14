LDLIBS=-lcrypto
CC = /usr/bin/gcc
CFLAGS = -Wall -Wextra -Wpedantic -O3 -w -march=native -fomit-frame-pointer -flto

THASH = robust

SOURCES =          hash_sha256.c hash_sha256x8.c thash_sha256_$(THASH).c thash_sha256_$(THASH)x8.c sha256.c sha256x8.c sha256avx.c address.c rng.c wots.c utils.c utilsx8.c fors.c sign.c
HEADERS = params.h hash.h        hashx8.h        thash.h                 thashx8.h               sha256.h sha256x8.h sha256avx.h address.h rng.h wots.h utils.h utilsx8.h fors.h api.h

DET_SOURCES = $(SOURCES:rng.%=rng.%)
DET_HEADERS = $(HEADERS:rng.%=rng.%)

.PHONY: clean 

default: benchmarks

all: benchmarks

benchmarks: benchmarks.c $(DET_SOURCES) $(DET_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(DET_SOURCES) $< -lcrypto

clean:
	-$(RM) benchmarks
