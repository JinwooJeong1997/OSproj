#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


#include"dirmng.h"
#include"vi.h"
#define MAX_CMD 256

//명령어는 여기에추가 하시오.
#define CMD_EXIT "exit"
#define CMD_HELP "help"
#define CMD_CREDIT "credit"
#define CMD_DIRMNG "dirmng"
#define CMD_IPCONFIG "ipconfig"
#define CMD_VI "vi" // vi + [파일명] 메모장 열기
//입력한 명령어가 cmp에 있는지 확인하는 함수. 있으면 1, 없으면 0 반환.
int checkCMD(char* target,char* cmp);
void print_prompt();


int main(void){
	char input[MAX_CMD];
	int pid;
	int status;
	while(1){
		print_prompt();
		fgets(input,MAX_CMD,stdin);
		if(!strcmp(input,"\n")){continue;}
		input[strlen(input)-1]='\0';
		if(checkCMD(input,CMD_EXIT)){break;}
		else if(checkCMD(input,CMD_CREDIT)){
			fputs("\n",stdout);
			fputs("======================\n",stdout);
			fputs("===TEAM9_OS_PROJECT===\n",stdout);
			fputs("======================\n",stdout);
		}	
		else if(checkCMD(input,CMD_HELP)){
			fputs("credit : \n",stdout);
		}
		else if(checkCMD(input,CMD_DIRMNG)){
			dirmng(input);
		}
		else if(checkCMD(input,CMD_IPCONFIG)){
			ipconfig();
		}
		else if(checkCMD(input,CMD_VI)){
			vi();
		}
		else{
			system(input);
		}
	//외부 명령어 실행시키는 부분
	fputs("\n",stdout);
	}
	fputs("EXIT myshell\n",stdout);
	return 0;
}

void print_prompt(){
	char *ps;
	char *index;
	if((ps = (char*)getenv("PS2")) != NULL){
		while(*ps != '\0'){
			if(*ps == '\\'){
				ps++;
				if(*ps == 'u'){ printf("%s",getenv("USER"));}
				else if(*ps == 'h'){printf("%s",getenv("HOSTNAME"));}
				else if(*ps == 'w'){printf("%s",(char*)get_current_dir_name());}
			}
		}
	}
	else{fputs(">>",stdout);} 
}	

int checkCMD(char* target,char* cmp){
	char * str = (char*)malloc(strlen(target));
	char * tmp = str;
	if(str == NULL){ fprintf(stderr,"error!\n");}
	strncpy(str,target,sizeof(target));
	char * cmd = strtok_r(str," ",&str);
	int result = 0;
	if(strncmp(cmd,cmp,sizeof(cmp))==0){
		result = 1;
	}
	str = tmp;
	free(str);
	return result;
}
