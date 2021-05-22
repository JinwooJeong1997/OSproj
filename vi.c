#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//#include"command.c"

#define MAX_CMD 256

//명령어는 여기에추가 하시오.
#define CMD_EXIT "exit"
#define CMD_HELP "help"
#define CMD_CREDIT "credit"

// vi 명령어
#define CMD_VI "vi " // vi + [파일명] 메모장 열기

void clrscr();
int write(); // 입력모드
int quit(); // 메모장 종료


int main(void) {
	char input[MAX_CMD];
	while (1) {
		fputs("myshell>>", stdout);
		fgets(input, MAX_CMD, stdin);
		input[strlen(input) - 1] = '\0';
		fputs(input, stdout);
		if (strncmp(input, CMD_EXIT, sizeof(CMD_EXIT)) == 0) {
			break;
		}
		//command compare 
		if (strncmp(input, CMD_CREDIT, sizeof(CMD_CREDIT)) == 0) {
			fputs("\n", stdout);
			fputs("======================\n", stdout);
			fputs("===TEAM9_OS_PROJECT===\n", stdout);
			fputs("======================\n", stdout);
		}
		if (strncmp(input, CMD_HELP, sizeof(CMD_HELP)) == 0) {
			//return cmd function with args...
			//somefunc(input);
			//command() in command.c
		}

		// vi+[파일명] 입력시 메모장 열기
		if (strstr(input, CMD_VI) != NULL) {
			clrscr();
			// 메모장모드
			int sel;
			fputs("1.Write\n", stdout);
			fputs("2.Quit\n", stdout);
			scanf_s("%d", &sel);
			switch (sel) {
			case 1:
				clrscr();
				write();
				break;
			case 2:
				clrscr();
				quit();
				break;
			}
		}
		fputs("\n", stdout);
	}
	fputs("EXIT myshell\n", stdout);
	return 0;
}

int quit() {
	int squit;
	printf("OUT?\n1.yes\n2.no\n");
	scanf_s("%d", &squit);
	switch (squit) {
	case 1:
		exit(0);
	case 2:
		clrscr();
		main();
		break;
	}
}

int write() {
	int i;
	char text[1000];
	char filename[MAX_CMD];
	printf("filename: ");
	scanf_s("%s", filename, MAX_CMD);
	strcat(filename, ".txt");
	FILE* fw = fopen(filename, "w");
	printf("Write\n");

	for (i = 0; i < 1000; i++) {
		fgets(text, sizeof(text), stdin);
		if (i == 0) {
			fputs("\b", fw);
		}
		fputs(text, fw);
		if (text[strlen(text) - 2] == '^') { // ^입력시 메모장 종료
			fclose(fw);
			main();
		}
	}
}

void clrscr() {
	system("cls");
}

int checkCMD(char* target, char* cmp) {
	return (strncmp(target, cmp, sizeof(cmp)) == 0) ? 1 : 0;

}