CC = gcc
target = myshell
all : $(target) 


#dirmng : dirmng.o
#	$(CC) -o dirmng dirmng.o

myshell : 
	$(CC)  -o $(target) shell_main.c dirmng.c

#dirmng.o : dirmng.c
#	$(CC) -c -o dirmng.o dirmng.c

clean :
	rm *.o $(target)

