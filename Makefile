libds.a: list.o vector.o map.o strutils.o
	ar rcs libds.a list.o vector.o map.o strutils.o

listtest: list.o listtest.c
	gcc -o listtest list.o listtest.c

list.o: list.h list.c
	gcc -c list.c

vector.o: vector.h vector.c
	gcc -c vector.c

vectest: vector.o vectest.c
	gcc -o vectest vector.o vectest.c

map.o: map.h map.c
	gcc -c map.c

maptest: vector.o map.o maptest.c
	gcc -o maptest vector.o map.o maptest.c
	
strutiltest: strutiltest.c strutils.o vector.o
	gcc strutiltest.c strutils.o vector.o -o strutiltest

strutils.o: strutils.h strutils.c
	gcc -c strutils.c

clean:
	rm -f *test *.o *.a
