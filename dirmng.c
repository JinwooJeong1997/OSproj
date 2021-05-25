//디렉토리 관리하는 명령어
// dirmng [-m/r/v/c/o] file file
//-m = mkdir
//-r = rmdir
//-v = mv
//-c = cp
//-o = chmod
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
void cmd_mv(int argc,char*argv[]){
	if(argc != 4){
		fprintf(stderr,"wrong args\n");
		return;
	}
	if(rename(argv[2],argv[3])){
		fprintf(stderr,"mv %s to %s failed\n",argv[2],argv[3]);
	}
}
void cmd_cp(int argc,char*argv[]){
	FILE * fp[2];
	if(argc != 4){
		fprintf(stderr,"wrong args\n");
		return;
	}
	if((fp[0]= fopen(argv[2],"rb"))==NULL){
		fprintf(stderr,"fail to open <%s> \n",argv[2]);
		return;
	}
	if((fp[1] = fopen(argv[3],"wb"))==NULL){
		fprintf(stderr,"fail to open <%s> \n",argv[3]);
		fclose(fp[0]);
		return;
	}
	int count;
	char buffer[1024];
	while( (count=fread(buffer,sizeof(char),1024,fp[0])) != 0){
		fwrite(buffer,sizeof(char),count,fp[1]);
	}
	fclose(fp[0]);
	fclose(fp[1]);
}

void dirmng(char* input){
	char* token = NULL;
	char* rest = input; 
	int argc = 0 ;
	char *argv[MAXARG];
	char *op[] = {"-m","-r","-v","-c"};
	while((token=strtok_r(rest," ",&rest))){
		if(argc == MAXARG) { 
			printf("too many args\n");
			break;
		}
		argv[argc] = (char*)malloc(strlen(token)+1);
		strncpy(argv[argc],token,sizeof(token));
		if(argv[argc] == NULL){
			fprintf(stderr,"malloc() fail!\n");
			break;
		}
		argc ++;
	}
	
	//option check
	for(int i = 0; i < 4;i++){
		if(strncmp(argv[1],op[i],sizeof(argv[1]))==0){
			switch(i){
				case 0:	//mk
					cmd_mk(argc,argv);
					break;
				case 1:	//rm
					cmd_rm(argc,argv);
					break;
				case 2: //mv
					cmd_mv(argc,argv);
					break;
				case 3: //cp
					cmd_cp(argc,argv);
					break;
			}
		}
	}
	for(int i= 0; i < argc ; i++){
		free(argv[i]);
	}
}


