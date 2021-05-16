#include"dirmng.h"


void dirmng(char* input){
	char* token = NULL;
	char* rest = input; 
	while((token=strtok_r(rest," ",&rest))){
		printf("%s \n",token);
	}
}
/*
int main(int argc,char* argv[]){
	printf("this is dirmng.c, %d args comes in \n",argc);
	for(int i = 0; i < argc ; i++){
		printf("%s \n",argv[i]);
	}
	return 0;
}
*/

