CC = gcc
target = myshell
all :  myshell


myshell : 
	$(CC)  -o myshell shell_main.c dirmng.c ipconfig.c vi.c


clean :
	rm $(target)

