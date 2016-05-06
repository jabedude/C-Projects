# MinGW compilers
CC_32=i686-w64-mingw32-gcc
CC_64=x86_64-w64-mingw32-gcc
CC=$(CC_32)

# do NOT reorder functions and keep output smallish
CFLAGS=-fno-toplevel-reorder -falign-functions=1 -Os

COMMON_SRC=common.c \
		   pe.c

BINDSHELL_SRC=bindshell.c
BINDSHELL_BIN=bindshell.exe

CALC_SRC=runcalc.c
CALC_BIN=runcalc.exe

# testharness stuff
BINDSHELL_TESTHARNESS_C=bindshell_testharness.c
BINDSHELL_TESTHARNESS=bindshell_testharness.exe

CALC_TESTHARNESS_C=runcalc_testharness.c
CALC_TESTHARNESS=runcalc_testharness.exe

#
# make targets
#
.PHONY: all
all: $(BINDSHELL_BIN) $(BINDSHELL_TESTHARNESS) $(CALC_BIN) $(CALC_TESTHARNESS)

$(BINDSHELL_BIN): $(BINDSHELL_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(CALC_BIN): $(CALC_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDSHELL_TESTHARNESS_C): $(BINDSHELL_BIN)
	python extract.py --testharness $(BINDSHELL_BIN) > $@

$(BINDSHELL_TESTHARNESS): $(BINDSHELL_TESTHARNESS_C)
	$(CC) $(CFLAGS) -o $@ $^

$(CALC_TESTHARNESS_C): $(CALC_BIN)
	python extract.py --testharness $(CALC_BIN) > $@

$(CALC_TESTHARNESS): $(CALC_TESTHARNESS_C)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(CALC_BIN) $(BINDSHELL_BIN) *_testharness.*

