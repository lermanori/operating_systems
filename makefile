all: a.c
	gcc -g a.c
clean:
	rm *.exe
test:
	/bin/make all
	./a.exe < input.txt



	
