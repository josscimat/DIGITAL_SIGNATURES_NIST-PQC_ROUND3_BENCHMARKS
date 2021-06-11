
CC=gcc
WARNING_FLAGS= -Wall -Wextra -Wpedantic -Wshadow
CFLAGS= -O2 -march=native $(WARNING_FLAGS) -std=gnu99 -D__LINUX__ -D__X64__ -I./sha3 -w
#CFLAGS_DEBUG= -g -march=native $(WARNING_FLAGS) -std=gnu99 -fsanitize=address -D__LINUX__ -D__X64__ -I./sha3
CFLAGS_DEBUG= -g -march=native $(WARNING_FLAGS) -D__LINUX__ -D__X64__ -I./sha3
SHA3LIB=libshake.a
SHA3_PATH=sha3
LDFLAGS= $(SHA3_PATH)/$(SHA3LIB) 

SOURCES= picnic_impl.c picnic3_impl.c picnic.c lowmc_constants.c
PICNIC_OBJECTS= picnic_impl.o picnic3_impl.o picnic.o lowmc_constants.o hash.o picnic_types.o api.o tree.o 
PICNIC_LIB= libpicnic.a

EXECUTABLE_BENCHMARKS=benchmarks
RNG_NISTKAT=rng.o


all: $(SHA3LIB) $(SOURCES) $(PICNIC_LIB) $(EXECUTABLE_BENCHMARKS)

nistkat: CFLAGS+= -DUSE_NIST_KAT_INSECURE_RNG 
nistkat: LDFLAGS+=  $(RNG_NISTKAT) -lssl -lcrypto 
nistkat: clean $(RNG_NISTKAT) all $(EXECUTABLE_BENCHMARKS)

$(SHA3LIB):
		$(MAKE) -C $(SHA3_PATH) 

# debug build
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: all

$(RNG_NISTKAT):
		$(CC) rng.c -c $(CFLAGS) -I -o $@ 

$(EXECUTABLE_BENCHMARKS): $(EXECUTABLE_BENCHMARKS).c
		$(CC) $(@).c $(CFLAGS) $(PICNIC_LIB) -o $@ $(LDFLAGS) -lssl -lcrypto

.c.o: 
	    $(CC) -c $(CFLAGS) $< -o $@

$(PICNIC_LIB): $(PICNIC_OBJECTS)
	ar rcs $@ $^


docs:
	doxygen docs/doxygen.cfg

.PHONY: docs

clean:
	    rm *.o 2>/dev/null || true
	    rm *.exe 2>/dev/null || true
	
	    rm $(EXECUTABLE_BENCHMARKS) 2>/dev/null || true
		rm rng.o 2>/dev/null || true
		rm *.rsp 2>/dev/null || true
		rm *.req 2>/dev/null || true
		rm $(PICNIC_LIB) 2>/dev/null || true
		$(MAKE) -C $(SHA3_PATH) clean

# Run the whitespace tool 
# Install with 'sudo apt-get install uncrustify'
# Make sure you have staged your changes, so that you can easily undo changes
# made by uncrustify if necessary
