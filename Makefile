myshell : main.o
	gcc -o myshell main.o

main.o : shell_main.c
	gcc -c -o main.o shell_main.c

clean :
	rm *.o myshell
