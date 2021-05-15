#include<stdio.h>

//#include"command.c"

#define MAX_CMD 256

//명령어는 여기에추가 하시오.
#define CMD_EXIT "exit"
#define CMD_HELP "help"
#define CMD_CREDIT "credit"
int checkCMD(char* target,char* cmp);

int main(void){
	char input[MAX_CMD];
	while(1){
	fputs("myshell>>",stdout);
	fgets(input,MAX_CMD,stdin);
	input[strlen(input)-1]='\0';
	fputs(input,stdout);
	if(checkCMD(input,CMD_EXIT)){break;}
	//command compare 
	if(checkCMD(input,CMD_CREDIT)){
	fputs("\n",stdout);
	fputs("======================\n",stdout);
	fputs("===TEAM9_OS_PROJECT===\n",stdout);
	fputs("======================\n",stdout);
	}	
	if(strncmp(input,CMD_HELP,sizeof(CMD_HELP))==0){
	//return cmd function with args...
	//somefunc(input);
	//command() in command.c
	}
	}
	fputs("EXIT myshell\n",stdout);
	return 0;

}

int checkCMD(char* target,char* cmp){
	return (strncmp(target,cmp,sizeof(cmp))==0)? 1 : 0 ;

}
