/*
 * Mega Drive / Genesis SMD to ROM converter
 * by Zoe Blade, 2015
 *
 * Usage: "smd-to-bin *.smd *.SMD"
 *
 * Based heavily on Bart Trzynadlowski's GROM Version 0.75
 * Public domain
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB 1024

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	FILE      *outputFilePointer;
	uint8_t   inputBlock[16 * KB];
	uint8_t   outputBlock[16 * KB];
	uint8_t   blockNumber = 0;
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
			outputFilePointer = fopen(strcat(strtok(*argv, "."), ".bin"), "wb");
			blockNumber = 0;
			byteNumber = 0;

			do {
				/* Read a byte in */
				byte = getc(inputFilePointer);
				inputBlock[byteNumber] = byte;

				if (byteNumber == 16 * KB - 1) {
					/* The 16KB block's full.  Convert it. */
					for (byteNumber = 0; byteNumber < 8 * KB; byteNumber++) {
						outputBlock[byteNumber * 2] = inputBlock[byteNumber + 8 * KB];
						outputBlock[byteNumber * 2 + 1] = inputBlock[byteNumber];
					}

					/* Write a block out */
					for (byteNumber = 0; byteNumber < 16 * KB; byteNumber++) {
						putc(outputBlock[byteNumber], outputFilePointer);
					}

					blockNumber++;
					byteNumber = 0;
				} else {
					byteNumber++;
				}
			} while (byte != EOF);

			fclose(inputFilePointer);
			fclose(outputFilePointer);
			printf("%s converted (%d 16KB blocks)\n", *argv, blockNumber);
		}
	}

	return 0;
}
