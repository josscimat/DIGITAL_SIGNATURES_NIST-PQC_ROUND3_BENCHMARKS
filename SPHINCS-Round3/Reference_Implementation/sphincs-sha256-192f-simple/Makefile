LDLIBS=-lcrypto
CC = /usr/bin/gcc
CFLAGS = -Wall -Wextra -Wpedantic -O3 -w

HASH = sha256
THASH = simple

SOURCES =          address.c rng.c wots.c utils.c fors.c sign.c hash_$(HASH).c thash_$(HASH)_$(THASH).c
HEADERS = params.h address.h rng.h wots.h utils.h fors.h api.h  hash.h thash.h

ifeq ($(HASH),shake256)
	SOURCES += fips202.c
	HEADERS += fips202.h
endif
ifeq ($(HASH),haraka)
	SOURCES += haraka.c
	HEADERS += haraka.h
endif
ifeq ($(HASH),sha256)
	SOURCES += sha256.c
	HEADERS += sha256.h
endif

DET_SOURCES = $(SOURCES:rng.%=rng.%)
DET_HEADERS = $(HEADERS:rng.%=rng.%)

.PHONY: benchmarks

default: benchmarks

all: benchmarks

benchmarks: benchmarks.c $(DET_SOURCES) $(DET_HEADERS)
	$(CC) $(CFLAGS) -o $@ $(DET_SOURCES) $< -lcrypto

clean:
	-$(RM) benchmarks
