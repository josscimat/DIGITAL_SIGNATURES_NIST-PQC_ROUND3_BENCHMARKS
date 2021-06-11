# This Makefile compiles the implementation in this directory along with
# the known answer tests generator located in the
# ../../../KAT/generator/ directory. The output is an executable program
# in the build/ subdirectory, whose name starts with 'kat', followed by
# the implementation name (e.g. 'kat512int' for the 'falcon512int'
# implementation). This program, when executed, generates the .req and
# .rsp files in the expected NIST format.

.POSIX:

CC = gcc
CFLAGS = -W -Wall -O2 -w
LIBFLAGS = -lcrypto -lm
LD = c99
LDFLAGS = 
LIBS = 

OBJ1 = codec.o common.o fft.o fpr.o keygen.o nist.o rng.o shake.o sign.o vrfy.o benchmarks.o katrng.o

HEAD1 = api.h fpr.h inner.h katrng.h

benchmarks: $(OBJ1)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o benchmarks $(OBJ1) $(LIBS)

codec.o: codec.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o codec.o codec.c

common.o: common.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o common.o common.c

fft.o: fft.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o fft.o fft.c

fpr.o: fpr.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o fpr.o fpr.c

keygen.o: keygen.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o keygen.o keygen.c

nist.o: nist.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o nist.o nist.c

rng.o: rng.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o rng.o rng.c

shake.o: shake.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o shake.o shake.c

sign.o: sign.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o sign.o sign.c

vrfy.o: vrfy.c $(HEAD1)
	$(CC) $(CFLAGS) -c -o vrfy.o vrfy.c

katrng.o: katrng.c $(HEAD1)
	$(CC) $(CFLAGS) -I . -c -o katrng.o katrng.c
	
clean:
	-rm -f benchmarks $(OBJ1)
