/*
 * Mega Drive / Genesis ROM renamer
 * by Zoe Blade, 2015
 *
 * Usage: "bin-rename *.bin *.BIN"
 *
 * Based heavily on Bart Trzynadlowski's GROM Version 0.75
 * Public domain
 */

#include <stdio.h>
#include <stdlib.h>

#define KB 1024

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	FILE      *outputFilePointer;
	char      outputFilename[40] = "out.bin\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"; /* Up to 40 chars: 32 for the filename, 1 space, 3 for the regions, 1 dot, 3 for the extension. */
	int16_t   byte;
	int16_t   byteNumber;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			/* Loop through each file */
			inputFilePointer = fopen(*++argv, "rb");

			if (inputFilePointer == NULL) {
				continue;
			}

			fseek(inputFilePointer, 512, SEEK_SET);
			byteNumber = 0;

			fclose(inputFilePointer);
			rename (*argv, outputFilename);
			printf("%s renamed to %s\n", *argv, outputFilename);
		}
	}

	return 0;
}
