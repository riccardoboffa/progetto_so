CFLAGS = -std=c89 -pedantic -D EASY

main: main.c function.c conf.h header.h Makefile
	gcc $(CFLAGS) main.c function.c -o main

clean:
	$(RM) -f *.o main function *~

run:
	./main
