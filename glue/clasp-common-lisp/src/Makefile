CFLAGS=`pkg-config --cflags libclasp`
LDFLAGS=`pkg-config --libs libclasp`

ifeq ($(UNAME_S),Darwin)
	LIBEXT=dylib
	LIBFLAGS=-dynamic
else
	LIBEXT=so
	LIBFLAGS=-shared
endif

all: libstimclasp.so

libstimclasp.so: stim-clasp.cc
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} stim-clasp.cc
	clang++ ${LIBFLAGS} -L../../../build/out -Wl,--whole-archive -lstim -Wl,--no-whole-archive -o libstimclasp.so stim-clasp.o  ${LDFLAGS}

clean:
	rm -f *.o *.so
