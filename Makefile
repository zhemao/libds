OPTS=-O2 -Wall
LDFLAGS=-L. -lds
HEADERS=list.h vector.h hashmap.h strutils.h heap.h tree.h
OBJS=list.o vector.o hashmap.o strutils.o heap.o tree.o 

libds.a: $(OBJS)
	ar rcs libds.a $(OBJS)
	
ds.h: $(HEADERS)
	cat $(HEADERS) | sed -e 's/#include "vector.h"//' > ds.h

listtest: libds.a listtest.c
	gcc $(OPTS) listtest.c $(LDFLAGS) -o listtest 

list.o: list.h list.c
	gcc $(OPTS) -c list.c

vector.o: vector.h vector.c
	gcc $(OPTS) -c vector.c

vectest: libds.a vectest.c
	gcc $(OPTS) vectest.c $(LDFLAGS) -o vectest

hashmap.o: hashmap.h hashmap.c
	gcc $(OPTS) -c hashmap.c

maptest: libds.a maptest.c
	gcc $(OPTS) maptest.c $(LDFLAGS) -o maptest
	
strutiltest: strutiltest.c libds.a
	gcc $(OPTS) strutiltest.c $(LDFLAGS) -o strutiltest

strutils.o: strutils.h strutils.c
	gcc $(OPTS) -c strutils.c

heap.o: heap.h heap.c
	gcc $(OPTS) -c heap.c

heaptest: libds.a heaptest.c
	gcc $(OPTS) heaptest.c $(LDFLAGS) -o heaptest

tree.o: tree.h tree.c
	gcc $(OPTS) -c tree.c

treetest: treetest.c libds.a
	gcc $(OPTS) treetest.c $(LDFLAGS) -o treetest

clean:
	rm -f *test *.o *.a
