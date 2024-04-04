hash: sha256constants.o sha256.o hash.o 
	gcc -Wall -std=c99 -g hash.o sha256.o sha256constants.o -o hash

sha256test: sha256constants.o sha256.o sha256test.o 
	gcc -Wall -std=c99 -g sha256test.o sha256.o sha256constants.o -o sha256test

sha256test.o: sha256test.c sha256.h sha256constants.h
	gcc -Wall -std=c99 -g -c sha256test.c

sha256constants.o: sha256constants.c sha256constants.h
	gcc -Wall -std=c99 -g -c sha256constants.c

hash.o: hash.c sha256.h sha256constants.h
	gcc -Wall -std=c99 -g -c hash.c

sha256.o: sha256.c sha256.h sha256constants.h
	gcc -Wall -std=c99 -g -c sha256.c


clean:
	rm -f hash.o sha256constants.o sha256.o sha256test.o
	rm -f hash sha256test
	rm -f output.txt