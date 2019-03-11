all: a.exe
	gcc -g a.o -o a.exe
a.exe: a.o 
	gcc -g a.o -o a.exe
a.o: a.c polygonList.c polygon.c checks.c
	gcc -g -c a.c -o a.o 
clean:
	rm *.o
	rm *.exe
test:
	/bin/make all
	./a.exe < input.txt

