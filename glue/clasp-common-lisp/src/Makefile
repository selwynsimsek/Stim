CFLAGS=`pkg-config --cflags libclasp`
LDFLAGS=`pkg-config --libs libclasp`

ifeq ($(UNAME_S),Darwin)
	LIBEXT=dylib
	LIBFLAGS=-dynamic
else
	LIBEXT=so
	LIBFLAGS=-shared
endif

objects = stim_clasp.o stim_clbind.o translators.o

all: libstimclasp.so

$(objects): %.o: %.cc stim_clbind.h
	clang++ -static -c -I../../../src -fPIC ${CFLAGS} $<

libstimclasp.so: ${objects}
	clang++ ${LIBFLAGS} -L../../../build/out -Wl,--whole-archive -lstim -Wl,--no-whole-archive -o libstimclasp.so $^ ${LDFLAGS}

run: libstimclasp.so
	rlwrap clasp --eval '(ql:quickload :stim)' --eval '(in-package :stim)'

run-quit: libstimclasp.so
	time rlwrap clasp --eval '(ql:quickload :stim)' --eval '(uiop:quit)'

clean:
	rm -f *.o *.so
