vinyl: input.o vinyl.o inventory.o 
	gcc -Wall -std=c99 -g vinyl.o inventory.o input.o -o vinyl

input.o: input.c input.h
	gcc -Wall -std=c99 -g -c input.c

vinyl.o: vinyl.c inventory.h input.h
	gcc -Wall -std=c99 -g -c vinyl.c

inventory.o: inventory.c inventory.h input.h
	gcc -Wall -std=c99 -g -c inventory.c

clean:
	rm -f vinyl.o inventory.o input.o
	rm -f vinyl
	rm -f output.txt