CFLAGS=-O2 -Wall
LDFLAGS=-L. -lds
HEADERS=list.h vector.h hashmap.h strutils.h heap.h tree.h
OBJS=list.o vector.o hashmap.o strutils.o heap.o tree.o 
PREFIX=/usr/local

libds.a: $(OBJS)
	ar rcs libds.a $(OBJS)
	
ds.h: $(HEADERS)
	cat $(HEADERS) | sed -e 's/#include "vector.h"//' > ds.h

listtest: libds.a listtest.c
	gcc $(CFLAGS) listtest.c $(LDFLAGS) -o listtest 

vectest: libds.a vectest.c
	gcc $(CFLAGS) vectest.c $(LDFLAGS) -o vectest

maptest: libds.a maptest.c
	gcc $(CFLAGS) maptest.c $(LDFLAGS) -o maptest
	
strutiltest: strutiltest.c libds.a
	gcc $(CFLAGS) strutiltest.c $(LDFLAGS) -o strutiltest

heaptest: libds.a heaptest.c
	gcc $(CFLAGS) heaptest.c $(LDFLAGS) -o heaptest

treetest: treetest.c libds.a
	gcc $(CFLAGS) treetest.c $(LDFLAGS) -o treetest

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f *test *.o *.a

install: ds.h libds.a
	mkdir -p $(PREFIX)/lib
	cp libds.a $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	cp ds.h $(PREFIX)/include
