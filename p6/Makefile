CFLAGS += -Wall -g -std=c99
driver: input.o value.o map.o driver.o
	gcc $(CFLAGS) input.o value.o map.o driver.o -o driver

doubleTest: doubleTest.o value.o
	gcc $(CFLAGS) doubleTest.o value.o -o doubleTest

doubleTest.o: doubleTest.c value.h
	gcc $(CFLAGS) -c doubleTest.c

stringTest: stringTest.o value.o
	gcc $(CFLAGS) stringTest.o value.o -o stringTest

stringTest.o: stringTest.c value.h
	gcc $(CFLAGS) -c stringTest.c

mapTest: mapTest.o value.o map.o
	gcc $(CFLAGS) mapTest.o value.o map.o -o mapTest

mapTest.o: mapTest.c value.h map.h
	gcc $(CFLAGS) -c mapTest.c

driver.o: driver.c value.h map.h input.h
	gcc $(CFLAGS) -c driver.c

input.o: input.c input.h
	gcc $(CFLAGS) -c input.c

map.o: map.c map.h value.h
	gcc $(CFLAGS) -c map.c

value.o: value.c value.h 
	gcc $(CFLAGS) -c value.c


clean:
	rm -f driver.o input.o map.o value.o doubleTest.o stringTest.o mapTest.o
	rm -f driver doubleTest stringTest mapTest
	rm -f output.txt
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov