/* Gameboy ROM lister, by Zoe Blade */

/* See http://gbdev.gg8.se/wiki/articles/The_Cartridge_Header for the spec */

#include <stdio.h>
#include <string.h>

char title[16] = "                ";
char cartridgeType = '\0';

void describeFile(FILE *inputFilePointer, FILE *outputFilePointer) {
	fseek(inputFilePointer, 0x134, SEEK_SET);
	fread(title, 16, 1, inputFilePointer);
	fseek(inputFilePointer, 0x147, SEEK_SET);
	cartridgeType = getc(inputFilePointer);

	if (strlen(title) == 0) {
		strcpy(title, "-");
	}

	printf("%s\t", title);

	switch (cartridgeType) {
	case 0x00:
		printf("NONE\t-\t-\t");
		break;

	case 0x01:
		printf("MBC1\t-\t-\t");
		break;

	case 0x02:
		printf("MBC1\tRAM\t-\t");
		break;

	case 0x03:
		printf("MBC1\tRAM\tBAT\t");
		break;

	case 0x05:
		printf("MBC2\t-\t-\t");
		break;

	case 0x06:
		printf("MBC2\t-\tBAT\t");
		break;

	default:
		printf("-\t-\t-\t");
		break;
	}

	printf("\n");
	return;
}

int main(int argc, char *argv[]) {
	FILE *filePointer;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		printf("File\t");
		printf("Title\t");
		printf("MBC\t");
		printf("RAM\t");
		printf("BAT\t");
		printf("\n");

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
