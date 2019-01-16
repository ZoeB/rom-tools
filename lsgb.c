/* Gameboy ROM lister, by Zoe Blade */

/* See http://gbdev.gg8.se/wiki/articles/The_Cartridge_Header for the spec */

#include <stdio.h>
#include <string.h>

char title[16] = "                ";
char cartridgeType = '\0';
char rom = '\0';
char ram = '\0';

void describeFile(FILE *inputFilePointer, FILE *outputFilePointer) {
	fseek(inputFilePointer, 0x134, SEEK_SET);
	fread(title, 16, 1, inputFilePointer);
	fseek(inputFilePointer, 0x147, SEEK_SET);
	cartridgeType = getc(inputFilePointer);
	fseek(inputFilePointer, 0x148, SEEK_SET);
	rom = getc(inputFilePointer);
	fseek(inputFilePointer, 0x149, SEEK_SET);
	ram = getc(inputFilePointer);

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

	case 0x08:
		printf("NONE\tRAM\t-\t");
		break;

	case 0x09:
		printf("NONE\tRAM\tBAT\t");
		break;

	case 0x0B:
		printf("MMM1\t-\t-\t");
		break;

	case 0x0C:
		printf("MMM1\tRAM\t-\t");
		break;

	case 0x0D:
		printf("MMM1\tRAM\tBAT\t");
		break;

	case 0x11:
		printf("MBC3\t-\t-\t");
		break;

	case 0x12:
		printf("MBC3\tRAM\t-\t");
		break;

	case 0x13:
		printf("MBC3\tRAM\tBAT\t");
		break;

	case 0x19:
		printf("MBC5\t-\t-\t");
		break;

	case 0x1A:
		printf("MBC5\tRAM\t-\t");
		break;

	case 0x1B:
		printf("MBC5\tRAM\tBAT\t");
		break;

	default:
		printf("-\t-\t-\t");
	}

	switch (rom) {
	case 0x00:
		printf(" 32K\t");
		break;

	case 0x01:
		printf(" 64K\t");
		break;

	case 0x02:
		printf("128K\t");
		break;

	case 0x03:
		printf("256K\t");
		break;

	case 0x04:
		printf("512K\t");
		break;

	case 0x05:
		printf("  1M\t");
		break;

	case 0x06:
		printf("  2M\t");
		break;

	case 0x07:
		printf("  4M\t");
		break;

	case 0x08:
		printf("  8M\t");
		break;

	default:
		printf("   -\t");
	}

	switch (ram) {
	case 0x00:
		printf("NONE\t");
		break;

	case 0x01:
		printf("  2K\t");
		break;

	case 0x02:
		printf("  8K\t");
		break;

	case 0x03:
		printf(" 32K\t");
		break;

	case 0x04:
		printf("128K\t");
		break;

	case 0x05:
		printf(" 64K\t");
		break;

	default:
		printf("   -\t");
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
		printf("ROM\t");
		printf("RAM\t");
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
