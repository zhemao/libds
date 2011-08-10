OPTS=-O2
LDFLAGS=-L. -lds

libds.a: list.o vector.o map.o strutils.o
	ar rcs libds.a list.o vector.o map.o strutils.o
	
ds.h: list.h vector.h map.h strutils.h
	cat list.h vector.h map.h strutils.h > ds.h

listtest: libds.a listtest.c
	gcc $(OPTS) -static listtest.c $(LDFLAGS) -o listtest 

list.o: list.h list.c
	gcc $(OPTS) -c list.c

vector.o: vector.h vector.c
	gcc $(OPTS) -c vector.c

vectest: libds.a vectest.c
	gcc $(OPTS) -static vectest.c $(LDFLAGS) -o vectest

map.o: map.h map.c
	gcc $(OPTS) -c map.c

maptest: libds.a maptest.c
	gcc $(OPTS) -static maptest.c $(LDFLAGS) -o maptest
	
strutiltest: strutiltest.c libds.a
	gcc $(OPTS) -static strutiltest.c $(LDFLAGS) -o strutiltest

strutils.o: strutils.h strutils.c
	gcc $(OPTS) -c strutils.c

clean:
	rm -f *test *.o *.a
