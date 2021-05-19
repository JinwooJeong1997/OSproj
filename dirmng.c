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
//dirmng -m a b
void cmd_mv(int argc,char*argv[]){
	FILE* src;
	FILE* dst;
	char ch;
	if(argc < 4){
		fprintf(stderr,"WRONG ARGS\n");
		return;
	}

	if((src=fopen(argv[2],"r"))==NULL){
		fprintf(stderr,"%s FAILED TO OPEN\n",argv[2]);
		return;
	}
	if((dst=fopen(argv[3],"w"))==NULL){
		fprintf(stderr,"%s FAILED TO OPEN\n",argv[3]);
		return;
	}

	while(!feof(src)){
		ch =(char)fgetc(src);
		if(ch!= EOF){fputc((int)ch,dst);}
	}
	fclose(src);
	fclose(dst);
	unlink(argv[2]);
	printf("result : %s -> %s\n",argv[2],argv[3]);
}
void cmd_cp(int argc,char* argv[]){
	FILE* src;
	FILE* dst;
	char ch;
	if(argc < 4){
		fprintf(stderr,"WRONG ARGS\n");
		return;
	}

	if((src=fopen(argv[2],"r"))==NULL){
		fprintf(stderr,"%s FAILED TO OPEN\n",argv[2]);
		return;
	}
	if((dst=fopen(argv[3],"w"))==NULL){
		fprintf(stderr,"%s FAILED TO OPEN\n",argv[3]);
		return;
	}

	while(!feof(src)){
		ch =(char)fgetc(src);
		if(ch!= EOF){fputc((int)ch,dst);}
	}
	fclose(src);
	fclose(dst);
	printf("result : copy %s to %s\n",argv[2],argv[3]);
}

//dirmng -o file 1123
void cmd_mod(int argc,char* argv[]){
	//FILE *src;
	mode_t mod=0;
	mode_t tmp=0;
	printf("%s \n",argv[3]);
	if(strlen(argv[3]) != 4){
		fprintf(stderr,"wrong permission");
		return;
	}
	

	if(chmod(argv[2],strtol(argv[3],NULL,8))==-1){
		fprintf(stderr,"error!\n");
		return;
	}else { printf("success!\n");}
	
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
					cmd_mv(argc,argv);
					break;
				case 3:
					cmd_cp(argc,argv);
					break;
				case 4:
					cmd_mod(argc,argv);
					break;
			}
		}
	}
	for(int i= 0; i < argc ; i++){
		free(argv[i]);
	}
}

