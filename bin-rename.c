/*
 * Mega Drive / Genesis ROM renamer
 * by Zoe Blade, 2015
 *
 * Usage: "bin-rename *.bin *.BIN"
 *
 * Public domain
 */

#include <stdio.h>
#include <stdlib.h>

#define KB 1024

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	FILE      *outputFilePointer;
	char      outputFilename[36] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	int16_t   byte;
	int16_t   lastByte;
	int8_t    inputByteNumber;
	int8_t    outputByteNumber;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			/* Loop through each file */
			inputFilePointer = fopen(*++argv, "rb");

			if (inputFilePointer == NULL) {
				continue;
			}

			outputByteNumber = 0;
			fseek(inputFilePointer, 0x150, SEEK_SET);

			for (inputByteNumber = 0; inputByteNumber < 32; inputByteNumber++) {
				byte = getc(inputFilePointer);

				if (byte == ' ') {
					byte = '-';
				}

				if (byte >= 'A' && byte <= 'Z') {
					/* Make names lowercase */
					byte += 0x20;
				}

				if (byte == '-' && lastByte == '-') {
					/* Ignore multiple spaces in a row */
					continue;
				}

				outputFilename[outputByteNumber] = byte;
				outputByteNumber++;
				lastByte = byte;
			}

			outputFilename[outputByteNumber] = '.';
			outputByteNumber++;
			outputFilename[outputByteNumber] = 'b';
			outputByteNumber++;
			outputFilename[outputByteNumber] = 'i';
			outputByteNumber++;
			outputFilename[outputByteNumber] = 'n';
			outputByteNumber++;

			while (outputByteNumber < 36) {
				outputFilename[outputByteNumber] = '\0';
				outputByteNumber++;
			}

			fclose(inputFilePointer);
			rename (*argv, outputFilename);
			printf("%s renamed to %s\n", *argv, outputFilename);
		}
	}

	return 0;
}
