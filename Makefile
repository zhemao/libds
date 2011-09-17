OPTS=-O2
LDFLAGS=-L. -lds
HEADERS=list.h vector.h hashmap.h strutils.h

libds.a: list.o vector.o hashmap.o strutils.o
	ar rcs libds.a list.o vector.o hashmap.o strutils.o
	
ds.h: $(HEADERS)
	cat $(HEADERS) | sed -e 's/#include "vector.h"//' > ds.h

listtest: libds.a listtest.c
	gcc $(OPTS) -static listtest.c $(LDFLAGS) -o listtest 

list.o: list.h list.c
	gcc $(OPTS) -c list.c

vector.o: vector.h vector.c
	gcc $(OPTS) -c vector.c

vectest: libds.a vectest.c
	gcc $(OPTS) -static vectest.c $(LDFLAGS) -o vectest

hashmap.o: hashmap.h hashmap.c
	gcc $(OPTS) -c hashmap.c

maptest: libds.a maptest.c
	gcc $(OPTS) -static maptest.c $(LDFLAGS) -o maptest
	
strutiltest: strutiltest.c libds.a
	gcc $(OPTS) -static strutiltest.c $(LDFLAGS) -o strutiltest

strutils.o: strutils.h strutils.c
	gcc $(OPTS) -c strutils.c

clean:
	rm -f *test *.o *.a
