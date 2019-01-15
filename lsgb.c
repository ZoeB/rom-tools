/* Gameboy ROM lister, by Zoe Blade */

/* See http://gbdev.gg8.se/wiki/articles/The_Cartridge_Header for the spec */

#include <stdio.h>

void describeFile(FILE *inputFilePointer, FILE *outputFilePointer) {
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
