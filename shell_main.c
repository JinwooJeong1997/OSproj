#include<stdio.h>
#include"command.c"
#define MAX_CMD 256


#define CMD_EXIT "exit"
#define CMD_HELP "help"


int main(void){
	char input[MAX_CMD];
	while(1){
	fputs("myshell>>",stdout);
	fgets(input,MAX_CMD,stdin);
	input[strlen(input)-1]='\0';
	fputs(input,stdout);
	if(strncmp(input,CMD_EXIT,sizeof(CMD_EXIT))==0){
		fputs("\nexit myshell!\n",stdout);
		return 0;
	}
	//command compare 	
	if(strncmp(input,CMD_HELP,sizeof(CMD_HELP))==0){
	//return cmd function with args...
	//somefunc(input);
	//command() in command.c
	}
	fputs("\n",stdout);
	}
	return 0;

}
