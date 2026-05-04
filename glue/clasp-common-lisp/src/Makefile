CFLAGS=$(shell pkg-config --cflags libclasp)
LDFLAGS=$(shell pkg-config --libs libclasp)

CXXFLAGS=$(shell llvm-config-17 --cxxflags)

CLANG=$(shell llvm-config-17 --bindir)/clang++

MAKEFLAGS += -j8

ifeq ($(UNAME_S),Darwin)
	LIBEXT=dylib
	LIBFLAGS=-dynamic
else
	LIBEXT=so
	LIBFLAGS=-shared
endif

objects = stim_clasp.o stim_clbind.o translators.o enums.o

all: libstimclasp.so

$(objects): %.o: %.cc stim_clasp.h
	$(CLANG) -static -c -I../../../src -fPIC $(CFLAGS) $<

libstimclasp.so: ${objects}
	$(CLANG) ${LIBFLAGS} -L../../../build/out -Wl,--whole-archive -lstim -Wl,--no-whole-archive -o libstimclasp.so $^ ${LDFLAGS}

run: libstimclasp.so
	rlwrap clasp --eval '(ql:quickload :stim)' --eval '(in-package :stim)'

run-quit: libstimclasp.so
	time rlwrap clasp --eval '(ql:quickload :stim)' --eval '(uiop:quit)'

clean:
	rm -f *.o *.so
