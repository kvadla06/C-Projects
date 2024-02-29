vcalc: vcalc.o vigesimal.o check.o
	gcc -Wall -std=c99 -g vcalc.o vigesimal.o check.o -o vcalc

vcalc.o: vcalc.c vigesimal.h check.h
	gcc -Wall -std=c99 -g -c vcalc.c

vigesimal.o: vigesimal.c vigesimal.h check.h
	gcc -Wall -std=c99 -g -c vigesimal.c

check.o: check.c check.h
	gcc -Wall -std=c99 -g -c check.c

clean:
	rm -f vcalc.o vigesimal.o check.o
	rm -f vcalc
	rm -f output.txt
