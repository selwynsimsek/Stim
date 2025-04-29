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

stim_clasp.o: stim_clasp.cc stim_clbind.h
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} stim_clasp.cc

stim_clbind.o: stim_clbind.cc stim_clbind.h
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} stim_clbind.cc

libstimclasp.so: stim_clasp.o stim_clbind.o
	clang++ ${LIBFLAGS} -L../../../build/out -Wl,--whole-archive -lstim -Wl,--no-whole-archive -o libstimclasp.so stim_clasp.o stim_clbind.o ${LDFLAGS}

run:
	clasp --eval '(ql:quickload :stim)'

run-quit:
	time clasp --eval '(ql:quickload :stim)' --eval '(uiop:quit)'

clean:
	rm -f *.o *.so
