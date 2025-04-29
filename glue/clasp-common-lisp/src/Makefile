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

libstimclasp.so: stim_clasp.cc stim_clbind.cc
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} stim_clasp.cc
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} stim_clbind.cc
	clang++ ${LIBFLAGS} -L../../../build/out -Wl,--whole-archive -lstim -Wl,--no-whole-archive -o libstimclasp.so stim_clasp.o stim_clbind.o ${LDFLAGS}

clean:
	rm -f *.o *.so
