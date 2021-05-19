//디렉토리 관리하는 명령어
// dirmng [-m/r/v/c/o] file file
//-m = mkdir
//-r = rmdir
//-v = mv
//-c = cp
//-o = chmod
//
#include"dirmng.h"

#define MAXARG 10
void cmd_mk(int argc,char*argv[]){
	if(argc != 3){
		fprintf(stderr,"wrong args\n");
		return;
	}

	if(mkdir(argv[2],0755)){
		fprintf(stderr,"mk fail\n");
	}
}
void cmd_rm(int argc,char*argv[]){
	if(argc < 2){
		fprintf(stderr,"wrong args\n");
		return;
	}
	for(int i = 2; i < argc; i++){
		if(rmdir(argv[i])){
			fprintf(stderr,"removing %s failed.\n",argv[i]);
		}
	}
}
void cmd_mv(){
}
void cmd_cp(){
}
void cmd_mod(){
}

void dirmng(char* input){
	char* token = NULL;
	char* rest = input; 
	int argc = 0 ;
	char *argv[MAXARG];
	char *op[] = {"-m","-r","-v","-c","-o"};
	while((token=strtok_r(rest," ",&rest))){
		if(argc == MAXARG) { 
			printf("too many args\n");
			break;
		}
		printf("%s \n",token);
		argv[argc] = (char*)malloc(strlen(token)+1);
		strncpy(argv[argc],token,sizeof(token));
		if(argv[argc] == NULL){
			fprintf(stderr,"malloc() fail!\n");
			break;
		}
		argc ++;
	}
	
	//option check
	printf("checking\n");
	for(int i = 0; i < 5;i++){
		if(strncmp(argv[1],op[i],sizeof(argv[1]))==0){
			switch(i){
				case 0:
					cmd_mk(argc,argv);
					break;
				case 1:
					cmd_rm(argc,argv);
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
			}
		}
	}
	for(int i= 0; i < argc ; i++){
		free(argv[i]);
	}
}


