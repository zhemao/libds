listtest: list.o listtest.c
	gcc -ggdb -o listtest list.o listtest.c

list.o: list.h list.c
	gcc -ggdb -c list.c

vector.o: vector.h vector.c
	gcc -c vector.c

vectest: vector.o vectest.c
	gcc -o vectest vector.o vectest.c

map.o: map.h map.c
	gcc -c map.c

maptest: vector.o map.o maptest.c
	gcc -o maptest vector.o map.o maptest.c

clean:
	rm -f *test *.o 
