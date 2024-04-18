driver: input.o value.o map.o driver.o
	gcc -Wall -std=c99 -g input.o value.o map.o driver.o -o driver

doubleTest: doubleTest.o value.o
	gcc -Wall -std=c99 -g doubleTest.o value.o -o doubleTest

doubleTest.o: doubleTest.c value.h
	gcc -Wall -std=c99 -g -c doubleTest.c

stringTest: stringTest.o value.o
	gcc -Wall -std=c99 -g stringTest.o value.o -o stringTest

stringTest.o: stringTest.c value.h
	gcc -Wall -std=c99 -g -c stringTest.c

mapTest: mapTest.o value.o map.o
	gcc -Wall -std=c99 -g mapTest.o value.o map.o -o mapTest

mapTest.o: mapTest.c value.h map.h
	gcc -Wall -std=c99 -g -c mapTest.c

driver.o: driver.c value.h map.h input.h
	gcc -Wall -std=c99 -g -c driver.c

input.o: input.c input.h
	gcc -Wall -std=c99 -g -c input.c

map.o: map.c map.h value.h
	gcc -Wall -std=c99 -g -c map.c

value.o: value.c value.h 
	gcc -Wall -std=c99 -g -c value.c


clean:
	rm -f driver.o input.o map.o value.o doubleTest.o stringTest.o mapTest.o
	rm -f driver doubleTest stringTest mapTest
	rm -f output.txt