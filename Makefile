CFLAGS = -Wall -Wpedantic

all: process
	$(MAKE) run
	
process: function.o process.o
	gcc $(CFLAGS) function.o process.o -o process

function.o:
	gcc $(CFLAGS) -c function.c -o function.o

run: 
	./process
	
clean:
	rm *.o

 


 



