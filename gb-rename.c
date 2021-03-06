/*
 * Gameboy ROM renamer
 * by Zoe Blade, 2015
 *
 * Usage: "gb-rename *.gb *.GB"
 *
 * Public domain
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	char      outputFilename[35] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
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
			fseek(inputFilePointer, 0x134, SEEK_SET);

			for (inputByteNumber = 0; inputByteNumber < 32; inputByteNumber++) {
				byte = getc(inputFilePointer);

				if (byte == '\0') {
					break;
				} else if (byte >= 'A' && byte <= 'Z') {
					/* Make uppercase letters lowercase */
					byte += 0x20;
				} else if (byte >= 'a' && byte <= 'z') {
					/* Leave lowercase letters alone */
				} else if (byte >= '0' && byte <= '9') {
					/* Leave numbers alone */
				} else if (byte == '&') {
					/* Spell out ampersands */

					if (lastByte == '-') {
						outputFilename[outputByteNumber] = 'a';
						outputByteNumber++;
						outputFilename[outputByteNumber] = 'n';
						outputByteNumber++;
						byte = 'd';
					} else {
						outputFilename[outputByteNumber] = '-';
						outputByteNumber++;
						outputFilename[outputByteNumber] = 'a';
						outputByteNumber++;
						outputFilename[outputByteNumber] = 'n';
						outputByteNumber++;
						outputFilename[outputByteNumber] = 'd';
						outputByteNumber++;
						byte = '-';
					}
				} else {
					/* Convert spaces (and everything else) to dashes */
					byte = '-';

					if (lastByte == '-') {
						/* Ignore multiple dashes in a row */
						continue;
					}
				}

				outputFilename[outputByteNumber] = byte;
				outputByteNumber++;
				lastByte = byte;
			}

			if (byte == '-') {
				/* Ditch any trailing space */
				outputByteNumber--;
			}

			outputFilename[outputByteNumber] = '.';
			outputByteNumber++;
			outputFilename[outputByteNumber] = 'g';
			outputByteNumber++;
			outputFilename[outputByteNumber] = 'b';
			outputByteNumber++;

			while (outputByteNumber < 35) {
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
