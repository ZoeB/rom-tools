/* Gameboy ROM lister, by Zoe Blade */

/* See http://gbdev.gg8.se/wiki/articles/The_Cartridge_Header for the spec */

#include <stdio.h>
#include <string.h>

char title[16] = "                ";

void describeFile(FILE *inputFilePointer, FILE *outputFilePointer) {
	fseek(inputFilePointer, 0x134, SEEK_SET);
	fread(title, 16, 1, inputFilePointer);

	if (strlen(title) == 0) {
		strcpy(title, "-");
	}

	printf("%s\t", title);
	return;
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			filePointer = fopen(*++argv, "r");

			if (filePointer == NULL) {
				continue;
			}

			printf("%s\t", *argv);
				describeFile(filePointer, stdout);
			fclose(filePointer);
		}
	}

	return 0;
}
