CC=    gcc
LD=    gcc

CFLAGS= -O3 -Wall -Wextra -fno-omit-frame-pointer -w
INCPATH= -I/usr/local/include -I/opt/local/include -I/usr/include 
LDFLAGS= 
LIBPATH= -L/usr/local/lib -L/opt/local/lib -L/usr/lib
LIBS=    -lcrypto -lm


ifeq ($(shell pwd | tail -c 5),avx2)
CFLAGS += -mavx2
CXXFLAGS += -mavx2
endif

ifeq ($(shell pwd | tail -c 6),ssse3)
CFLAGS += -mssse3
CXXFLAGS += -mssse3
endif



SRCS = $(wildcard *.c)
SRCS_O = $(SRCS:.c=.o)
SRCS_O_ND = $(subst ,,$(SRCS_O))

OBJ = $(SRCS_O_ND)

EXE= benchmarks


CSRC= $(wildcard *.c)


ifdef DEBUG
        CFLAGS=  -D_DEBUG_ -g -O1 -mavx2 -std=c99 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer
        CXXFLAGS= -D_DEBUG_ -g -O1 -mavx2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdinc++
endif

ifdef GPROF
	CFLAGS += -pg
	CXXFLAGS += -pg
	LDFLAGS += -pg
endif

.PHONY: all tests tables clean

all: $(OBJ) $(EXE)

benchmarks: $(OBJ) benchmarks.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

rainbow-genkey: $(OBJ) rainbow-genkey.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

rainbow-sign: $(OBJ) rainbow-sign.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

rainbow-verify: $(OBJ) rainbow-verify.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCPATH) -c $<

clean:
	rm *.o benchmarks;
