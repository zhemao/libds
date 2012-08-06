CFLAGS=-O2 -Wall
LDFLAGS=-L. -lds
HEADERS=list.h vector.h hashmap.h strutils.h heap.h tree.h
OBJS=list.o vector.o hashmap.o strutils.o heap.o tree.o 
PREFIX=/usr/local
CC=gcc

libds.a: $(OBJS)
	ar rcs libds.a $(OBJS)

test: listtest vectest maptest strutiltest heaptest treetest
	
ds.h: $(HEADERS)
	cat $(HEADERS) | sed -e 's/#include "vector.h"//' > ds.h

%test: %test.c libds.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *test *.o *.a

install: ds.h libds.a
	mkdir -p $(PREFIX)/lib
	cp libds.a $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	cp ds.h $(PREFIX)/include
