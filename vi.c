#include "vi.h"


void vi() {
	clrscr();
	// 메모장모드
	int sel;
	fputs("1.vi_write\n", stdout);
	fputs("2.Quit\n", stdout);
	scanf("%d", &sel);
	switch (sel) {
	case 1:
		clrscr();
		vi_write();
		break;
	case 2:
		clrscr();
		quit();
		break;
	}
}

int quit() {
	int squit;
	printf("OUT?\n1.yes\n2.no\n");
	scanf("%d", &squit);
	switch (squit) {
	case 1:
		clrscr();
        break;
	case 2:
		clrscr();
		vi();
		break;
	}
}

int vi_write() {
	int i;
	char text[1000];
	char filename[MAX_CMD];
	printf("filename: ");
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE* fw = fopen(filename, "w");
	printf("write\n");

	for (i = 0; i < 1000; i++) {
		fgets(text, sizeof(text), stdin);
		if (i == 0) {
			fputs("\b", fw);
		}
		fputs(text, fw);
		if (text[strlen(text) - 2] == '^') { // ^입력시 메모장 종료
			fclose(fw);
            quit();
            break;
		}
	}
}

void clrscr() {
	system("clear");
}